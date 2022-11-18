#include <sys/mman.h>
#include <pthread.h>
#include "common_shm.h"
#include "common.h"

int main(int argc, char *argv[])
{
	// create POSIX shared memory buffer
	int shmFd = shm_open(SHM_NAME, O_RDWR, FILE_MODE);
	if(shmFd < 0){
	        printf("shm_open error: %s\n", strerror(errno));
		CLOGE("create shared memory buffer failed!");
		exit(0);
	}
	
	ShmIntInt* ptr_shm = (ShmIntInt*) mmap(NULL,sizeof(ShmIntInt), PROT_READ|PROT_WRITE, MAP_SHARED,shmFd,0);

	if(ptr_shm == MAP_FAILED){
		CLOGE("mmap failed.");
		exit(0);
	}
	close(shmFd);

	char instr;
	int key, val;
	printf("Your Request:(I/R/D):\n");
	while(ptr_shm->count < MAXLOOP && scanf(" %c",&instr)==1){
		int flag;
		switch(instr){
			case 'I':
				flag = INSERT;
				printf("The entry:(key value)\n");
				scanf(" %d %d",&key,&val);
				break;
			case 'R':
				flag = READ;
				printf("The entry:(key)\n");
				scanf(" %d",&key);
				break;
			case 'D':
				flag = DELETE;
				printf("The entry:(key)\n");
				scanf(" %d",&key);
				break;
			default:
				CLOGE("Wrong instruction!");
				printf("%p %c\n",&instr, instr);
				exit(0);// TODO : go back to loop
		}
		ptr_shm->count++;
		ptr_shm->hash_operation = flag;
		ptr_shm->key = key;
		ptr_shm->val = val;
		
		sem_post(&ptr_shm->sem_c);
		
		sem_wait(&ptr_shm->sem_s);


		if(flag==READ){
			if(ptr_shm->flag)
				printf("Get data entry [%d:%d] from the hash table.\n",key,ptr_shm->val);
			else
				printf("There is no %d as the key in the hash table.\n",key);
		}
		if(ptr_shm->count < MAXLOOP)
			printf("Your Request:(I/R/D):\n");
		else
			printf("Too Many Requests!\n");
	}

	exit(0);

}
