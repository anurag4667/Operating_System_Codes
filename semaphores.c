#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

sem_t full , empty;
pthread_t t1,t2;
char buffer;
char myword[] = "HELLO WORLD";


void * producer(){
	
	for(int i = 0; myword[i] != '\0'; i++){
		sem_wait(&empty);

		buffer = myword[i];

		printf("producer added character : %c\n", buffer);

		sem_post(&full);

		sleep(1);
	}

}

void * consumer(){
	
	for(int i = 0; i < 11; i++){
		sem_wait(&full);

		printf("consumer readed character : %c\n",buffer);

		sem_post(&empty);

		sleep(1);
	}

}


int main(){
	sem_init(&full,0,0);
	sem_init(&empty,0,1);
	
	pthread_create(&t1,NULL,producer,NULL);
	pthread_create(&t2,NULL,consumer,NULL);
	

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&full);
	sem_destroy(&empty);

}

