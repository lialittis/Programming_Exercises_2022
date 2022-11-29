#include <pthread.h>
 
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
int r=0,w=0;

void reader(){
	// r_lock steps
	pthread_mutex_lock(&mutex); // lock mutex     
	while(w != 0) // there are writers waiting
	{
     		pthread_cond_wait(&cond, &mutex);
	}

	r++; // increment readers
	
	pthread_mutex_unlock(&mutex); // unlock mutex
	
	//critical reading code
	
	// r_unlock steps
	pthread_mutex_lock(&mutex);
	r--;
	if(r == 0)
     		pthread_cond_broadcast(&cond); // wake up
	pthread_mutex_unlock(&mutex);

}

void writer(){ 
	// w_lock steps
	pthread_mutex_lock(&mutex);
	while(w != 0 || r > 0)
	{	
     		pthread_cond_wait(&cond, &mutex);
	}
	w = 1;
	pthread_mutex_unlock(&mutex);
	
	// critical writing code

	// w_unlock steps
	pthread_mutex_lock(&mutex);
	w = 0;
	pthread_cond_broadcast(&cond); // wake up
	pthread_mutex_unlock(&mutex);
}
 
