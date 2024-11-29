#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(){
	pid_t pid=fork();
	if(pid<0){
		perror("fork faild");
	}
	else if(pid==0){
		printf("Child: Executing 'ls' command\n");
		execlp("ls","ls",NULL);
		perror("execlp failed");
	}
	else{
		printf("Parent: Waiting for child to complete...\n");
		wait(NULL);
		printf("Parent: Child completed. Now parent continues.\n");
	}
	return 0;
}