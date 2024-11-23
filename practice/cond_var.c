#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int totalfuel = 100;


void * fueladder(){
	
	for(int i = 0; i < 5; i++){
	pthread_mutex_lock(&mutex);
	totalfuel+= 20;
	printf("added fuel %d\n", totalfuel);
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	sleep(1);
	}

}

void * fillfuel(){
	
	pthread_mutex_lock(&mutex);
	//conditions
	while(totalfuel < 40){
	printf("not enough fuel available waiting .....\n");
	pthread_cond_wait(&cond,&mutex);
	}

	totalfuel -=40;
	printf("got fuel %d\n", totalfuel);
	pthread_mutex_unlock(&mutex);

}

int main(){
	pthread_t cars[5];
	pthread_t pp;

	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	
	pthread_create(&pp, NULL , fueladder,NULL);

	for(int i = 0; i < 5; i++){
		pthread_create(&cars[i],NULL , fillfuel,NULL);
	}

	for(int i = 0; i < 5; i++){
		pthread_join(cars[i],NULL);
	}

	pthread_join(pp,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

}

