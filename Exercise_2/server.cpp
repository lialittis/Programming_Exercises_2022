#include <sys/mman.h>
#include <pthread.h>
#include <cstdio>
#include "common_shm.h"
#include "include/common.h"
#include "my_hash.h"

int main(int argc, char *argv[])
{

	if (argc != 2) {
        	fprintf(stderr, "Usage: %s Hash_Size\n", argv[0]);
                exit(EXIT_FAILURE);
        }

	int hash_size = atoi(argv[1]);
	HashTable<int,int>* ht = new HashTable<int,int>(hash_size);

	// create POSIX shared memory buffer
	
	// unlink the shared memory buffer if it is already open.
	shm_unlink(SHM_NAME);
	printf("%s\n",SHM_NAME);
	// shm_open : open shared memory
	int shmFd = shm_open(SHM_NAME, O_RDWR|O_CREAT|O_EXCL, FILE_MODE);
	if(shmFd < 0){
		errExit("create shared memory buffer failed!");
	}
	
	// ftruncate : set size
	if(ftruncate(shmFd, sizeof(ShmIntInt)) == -1)
		errExit("ftruncate failed");
	// mmap : map to virtual memory
	ShmIntInt* ptr_shm = (ShmIntInt*) mmap(NULL,sizeof(ShmIntInt), PROT_READ|PROT_WRITE, MAP_SHARED,shmFd,0);

	if(ptr_shm == MAP_FAILED){
		errExit("map failed");
	}
	// close fd
	close(shmFd);

	// Initialize semaphore that is shared between processes
	sem_init(&ptr_shm->sem_s,1,0); // TODO: check the error here
	sem_init(&ptr_shm->sem_c,1,0); // TODO: check the error here

	while(ptr_shm->count < MAXLOOP){

		sem_wait(&ptr_shm->sem_c);
		
		printf("server count : %d\n",ptr_shm->count);
		switch(ptr_shm->hash_operation){
			case INSERT:
				ht->insert(ptr_shm->key,ptr_shm->val);
				break;
			case READ:
				{
				int v = ht->get(ptr_shm->key);
				ptr_shm->val = v;
				}
				break;

			case DELETE:
				ht->delete_key(ptr_shm->key);
				break;
			default:
				SLOGE("Wrong Instruction!");
		}
		sem_post(&ptr_shm->sem_s);
	}

	printf("Too Many Requests! I am going to take a break..\n");

	sem_destroy(&ptr_shm->sem_c);
	sem_destroy(&ptr_shm->sem_s);

	exit(0);
}
