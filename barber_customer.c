#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

typedef enum states {
	SLEEPING,
	WORKING
} States;

int waiting_customer = 0;
sem_t b_chair,c_ready, haircut_finish;
pthread_mutex_t mutex;

void * barberfunc(){
	
	while(1){
		
		sem_wait(&c_ready);
		pthread_mutex_lock(&mutex);
		waiting_customer--;
		printf("barber is cutting hair. waiting customers %d\n", waiting_customer);
		pthread_mutex_unlock(&mutex);
		sleep(2);
		printf("haircut finished\n");
		sem_post(&haircut_finish);
	}
}

void * customerfunc(void * arg){
	int id = *(int *)arg;

	pthread_mutex_lock(&mutex);

	if(waiting_customer < 3){
		waiting_customer++;
		printf("customer %d arrived \n", id);
		
		sem_post(&c_ready)i

		pthread_mutex_unlock(&mutex);

		sem_wait(&b_chair);
		printf("customer %d is getting the haircut\n", id);
		
		sem_wait(&haircut_finish);
		
		sem_post(&b_chair);
	}
	else{
		printf("customer %d left the shop\n" , id);
		pthread_mutex_unlock(&mutex);
	}
}


int main(){
	pthread_t customers[10];
	pthread_t barber;
	int customer_id[10];

	pthread_mutex_init(&mutex,NULL);
	sem_init(&b_chair,0,1);
	sem_init(&c_ready,0,0);
	sem_init(&haircut_finish,0,0);
	pthread_create(&barber,NULL,barberfunc,NULL);

	for(int i = 0; i < 10; i++){
		customer_id[i] = i+1;
		pthread_create(&customers[i], NULL , customerfunc,&customer_id[i]);
		sleep(rand()%3);
	}

	for(int i = 0; i < 10; i++){
		pthread_join(customers[i], NULL);
	}
	
	pthread_cancel(barber);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&b_chair);
	sem_destroy(&c_ready);
	sem_destroy(&haircut_finish);

}
