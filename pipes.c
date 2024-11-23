#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	char buffer[100];
	int fd[2];
	int fd2[2];
	
	if(pipe(fd) == -1 || pipe(fd2) == -1){
	
		printf("pipe failed");
		exit(EXIT_FAILURE);
	}

	int id = fork();

	if(id < 0){
	      	printf("process creation failed");
		exit(EXIT_FAILURE);
	}

	else if(id > 0){
		close(fd[0]);
		close(fd2[1]);
		char msg[] = "hi this is parent process";

		write(fd[1],msg,sizeof(msg));
		
		wait(NULL);

		read(fd2[0],buffer,100);
		printf("from child : %s \n",buffer);
		
		close(fd[1]);
		close(fd2[0]);
	
	}
	else{
		close(fd[1]);
		close(fd2[0]);

		char msg[] = "hi from child process";
		write(fd2[1],msg,sizeof(msg));
		
		read(fd[0],buffer,100);
		printf("from parent : %s \n",buffer);
		
		close(fd[0]);
		close(fd2[1]);
	
	
	}


}
