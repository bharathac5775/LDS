#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid=fork();
	if(pid<0){
		perror("fork failed");
		return 1;
	}
	else if(pid==0){
		printf("the child process id is %d and parent process id is %d \n ",getpid(),getppid());
	}
	else{
		printf("the parent process id is %d and child process id is %d \n ",getpid(),pid);
	}
	return 0;
}