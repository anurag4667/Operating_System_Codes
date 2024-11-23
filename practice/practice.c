#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t forks[5];

void * func(void * arg){
	int id = *(int *) arg;

	printf("philosopher %d is thinking \n", id + 1);
	sleep(2);

	if(id%2){
		pthread_mutex_lock(&forks[id]);
		printf("philosopher %d has picked up left fork\n", id + 1);
		pthread_mutex_lock(&forks[(id + 4)%5]);
		printf("philosopher %d has picked up right fork\n", id + 1);

		printf("philosopher %d is eating\n", id + 1);
		sleep(3);
		pthread_mutex_unlock(&forks[id]);
		printf("philosopher %d put down left fork\n",id + 1);
		pthread_mutex_unlock(&forks[(id + 4)%5]);
		printf("philosopher %d put down right fork\n", id+1);
	}
	else{
		pthread_mutex_lock(&forks[(id + 4)%5]);
		printf("philosopher %d has picked up right fork\n", id+1);
		pthread_mutex_lock(&forks[id]);
		printf("philosopher %d has picked up left fork\n" , id+1);

		printf("philosopher %d is eating\n",id + 1);
		sleep(3);
		pthread_mutex_unlock(&forks[(id+4)%5]);
		printf("philosopher %d has put down right fork\n", id+1);
		pthread_mutex_unlock(&forks[id]);
		printf("philosopher %d has put down left fork\n" ,id+1);
	}
	
}

int main(){
	pthread_t philosophers[5];
	int p_id[5];
	

	for(int i = 0; i < 5; i++ ){
		pthread_mutex_init(&forks[i], NULL);
		p_id[i] = i;
	}

	for(int i = 0; i < 5; i++){
		pthread_create(&philosophers[i], NULL, func,&p_id[i] );
	}

	for(int i = 0; i < 5; i++){
		pthread_join(philosophers[i],NULL);
	}
	
	for(int i = 0; i < 5; i++)
		pthread_mutex_destroy(&forks[i]);

}
