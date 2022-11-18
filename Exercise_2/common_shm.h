#ifndef __COMMON_SHM_H__
#define __COMMON_SHM_H__


#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE	20
#define SHM_NAME 	"hash_requests"

//#define O_RDONLY        00
//#define O_WRONLY        01
//#define O_RDWR          02

struct SharedMem{
	char msg[MSG_SIZE];
	sem_t mutex;

	SharedMem(){
		memset(msg,0,sizeof(msg));
	}
};


#endif // __COMMON_SHM_H__
