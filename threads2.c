#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int arr[] = {1,2,3,4,5,6,7,8,9};
int sum[3] = {0,0,0};

void * routine(void * k){
	int x = *((int *)k);
	
	for(int i = x*3; i < x*3 + 3; i++){
		sum[x] += arr[i];
	}
	
	pthread_exit(0);
}

int main(){
	pthread_t thread[3];
	int threadind[3];	
	for(int i = 0; i < 3; i++){
		threadind[i] = i;
		pthread_create(&thread[i], NULL, routine, (void *) &threadind[i]);
	}

	for(int i = 0; i < 3; i++){
		pthread_join(thread[i], NULL);
	}

	int total = 0;
	for(int i = 0; i < 3; i++){
		printf("%d\n" , sum[i]);
		total += sum[i];
	}

	printf("the total sum is %d \n" , total);

}

