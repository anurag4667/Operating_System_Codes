#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>



void*  routine(void *a){
	int x = *((int *)a);
	int i = 1;
	for(;i <= x; i++){
		printf("%d \n", i);
		sleep(1);
	}

	
}


int main(){

	pthread_t t1,t2;
	// reference to t1,attributes, function to be executed (reference),arguments
	
       	int a = 10;	
	pthread_create(&t1,NULL, &routine,(void *)&a);
	pthread_create(&t2,NULL, &routine,(void *)&a);

	//basically wait but for threads
	// pointer, pointer that gets the result
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	return 0;


}

