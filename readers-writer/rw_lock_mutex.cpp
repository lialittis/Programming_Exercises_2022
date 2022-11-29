#include <pthread.h>

pthread_mutex_t countMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;   

int readerCount = 0; // number of current readers

// Writer Mode
void writer(){
	pthread_mutex_lock(&writeMutex);
	// critical writing code
	pthread_mutex_unlock(&writeMutex);
}

// Reader Mode
void reader(){
	// r_lock steps
	pthread_mutex_lock(&countMutex);
	readerCount++;
	if(readerCount == 1)
		pthread_mutex_lock(&writeMutex);
	pthread_mutex_unlock(&countMutex);

	// critical reading code
	
	// r_unlock steps
	pthread_mutex_lock(&countMutex);
	readerCount--;
	if(readerCount == 0)
		pthread_mutex_unlock(&writeMutex);
	pthread_mutex_unlock(&countMutex);
}

