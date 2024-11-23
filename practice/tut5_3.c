#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;
int balance = 1000;

void * addmoney(){

	for(int i = 0; i < 50; i++){
		pthread_mutex_lock(&mutex);
		balance += 50;
		printf("added 50 to the balance %d\n", balance);
		pthread_mutex_unlock(&mutex);
	}
}

void * withdraw(){
	for(int i = 0; i < 20; i++){
		pthread_mutex_lock(&mutex);
		balance -= 20;
		printf("withdraw 20 from the balance %d\n", balance);
		pthread_mutex_unlock(&mutex);
	
	}

}


int main(){
	pthread_t t1,t2;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&t1,NULL, addmoney,NULL);
	pthread_create(&t2,NULL, withdraw,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&mutex);

}
