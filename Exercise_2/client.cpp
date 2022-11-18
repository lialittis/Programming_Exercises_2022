#include <sys/mman.h>
#include <pthread.h>
#include "common_shm.h"
#include "include/common.h"

int main(int argc, char *argv[])
{
	// create POSIX shared memory buffer
	shm_unlink(SHM_NAME);
	int shmFd = shm_open(SHM_NAME, O_RDWR, 0664);
	if(shmFd < 0){
		LOGE("create shared memory buffer failed!");
		exit(0);
	}
	
	SharedMem* ptr_shm = (SharedMem*) mmap(NULL,sizeof(SharedMem), PROT_READ|PROT_WRITE, MAP_SHARED,shmFd,0);

	if(ptr_shm == MAP_FAILED){
		LOGE("mmap failed.");
		exit(0);
	}

	close(shmFd);

	// produce
	// TODO


}
