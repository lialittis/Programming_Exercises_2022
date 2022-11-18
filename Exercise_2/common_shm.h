#ifndef __COMMON_SHM_H__
#define __COMMON_SHM_H__

#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE	20
#define SHM_NAME 	"/hash_requests"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//#define O_RDONLY        00
//#define O_WRONLY        01
//#define O_RDWR          02

#define INSERT		00
#define READ 		01
#define DELETE		02
#define MAXLOOP		2000
#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)


template <class Key, class Value>
struct SharedMem{
	int count;
	sem_t sem_s;
	sem_t sem_c;
	size_t hash_operation;
	Key key;
	Value val;
};

typedef SharedMem<int,int> ShmIntInt;

#endif // __COMMON_SHM_H__
