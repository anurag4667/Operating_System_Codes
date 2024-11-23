#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t forks[5];


void * func( void * arg){
	int id = *(int *)arg;

	printf("philospher %d is thinking\n" , id);
	sleep(1);
	if(id == 4){
		pthread_mutex_lock(&forks[id]);
		printf("philosopher %d has picked up left fork\n",id);
		sleep(1);
		pthread_mutex_lock(&forks[(id + 4)%5]);
		printf("philosopher %d has picked up right fork\n",id);
		sleep(1);
	}
	else {
		pthread_mutex_lock(&forks[(id + 4)%5]);
		printf("philosopher %d has picked up right fork\n",id);
		sleep(1);
		pthread_mutex_lock(&forks[id]);
		printf("philosopher %d has picked up left fork\n",id);
		sleep(1);	
	}

	printf("philosopher %d is eating....\n",id);
	sleep(1);
	pthread_mutex_unlock(&forks[id]);
	printf("philosopher %d has put down left fork\n" , id);
	sleep(1);
	pthread_mutex_unlock(&forks[(id+4)%5]);
	printf("philosopher %d has put down right fork\n", id);
	sleep(1);
}


int main(){
	pthread_t p[5];
	int id[5];

	for(int i = 0; i < 5; i++){
		id[i] = i;
		pthread_mutex_init(&forks[i], NULL);
	}

	for(int i = 0;i < 5; i++){
		pthread_create(&p[i],NULL , func,&id[i]);
	
	}

	for(int i = 0; i < 5; i++){
		pthread_join(p[i],NULL);
	
	}
	for(int i = 0; i < 5; i++) pthread_mutex_destroy(&forks[i]);

}


