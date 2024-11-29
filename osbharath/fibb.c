#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void fibb(int n){
	int first ,second,i,next;
	first =1;
	second=1;
	printf("Fibonacci series up to %d numbers:\n", n);
	for(i=0;i<=n;i++){
		if(i==0 || i==1){
			printf("%d ", first);
		}
		else{
			next=first+second;
			printf("%d ",next);
			first=second;
			second=next;
		}
	}
	printf("\n");
}

int main(int argc ,char *argv[]){
	if(argc!=2){
		printf("Usage: %s <n>\n", argv[1]);
		return 1;
	}
	int n=atoi(argv[1]);
	if(n<=0){
		printf("Please provide a positive integer for n.\n");
        return 1;
	}
	pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // This is the child process
        printf("Child Process: Generating Fibonacci series...\n");
        fibb(n);
    } else {
        // This is the parent process
        wait(NULL);  // Wait for the child process to finish
        printf("Parent Process: Child has completed generating the series.\n");
    }

    return 0;
}