#include <semaphore.h>

sem_t r_sem;
sem_t w_sem;

int readers = 0;

// Writer Mode
void writer(){
	sem_wait(&w_sem);
	// critical writing code
	sem_post(&w_sem);
}

// Reader Mode
void reader(){
	// r_lock steps
	sem_wait(&r_sem);
	readers++;
	if(readers == 1)
     		sem_wait(&w_sem);
	sem_post(&r_sem);

	// critical reading code
	
	// r_unlock steps
	sem_wait(&r_sem);
	readers--;
	if(readers == 0)
     		sem_post(&w_sem);
	sem_post(&r_sem);
}

int main(){

	sem_init(&r_sem, 0, 1);
	sem_init(&w_sem, 0, 1);
	
	// ...
}
