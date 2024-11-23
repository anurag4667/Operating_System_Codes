#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void * func(){

	printf("HELLO WORLD\n");

}

int main(){

	pthread_t t[5];

	for(int i = 0; i < 5; i++){
		pthread_create(&t[i],NULL, func,NULL);
	}

	for(int i = 0; i < 5; i++){
		pthread_join(t[i],NULL);
	}

}
