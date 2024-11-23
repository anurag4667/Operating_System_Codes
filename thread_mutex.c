#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int total = 0;
pthread_mutex_t mutex;

void * sum(){

	for(int i = 0; i < 1000000; i++){
		pthread_mutex_lock(&mutex);
		//critical section
		total++;
		//critical section
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_t p1,p2;
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&p1,NULL, sum,NULL);
	pthread_create(&p2,NULL,sum,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_mutex_destroy(&mutex);

	printf("%d\n" , total);
}

