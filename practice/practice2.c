#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>


pthread_mutex_t mutex;
sem_t empty,full;
char buffer;
char message[] = "HELLO! WORLD";


void * consumer(){
	
	for(int i = 0; i < 12; i++){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		printf("characte read by consumer %c \n",buffer );
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(1);
	}

}

void * producer(){
	
	for(int i = 0; message[i] != '\0'; i++){
		
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		printf("character produced by producer %c \n", message[i]);
		buffer = message[i];
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(1);
	}	

}



int main(){
	pthread_t prod, cons;

	sem_init(&empty,0,1);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL , consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(prod,NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
}
