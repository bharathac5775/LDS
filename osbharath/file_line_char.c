#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void count_lines(const char *filename){
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		perror("failed to open the file\n");
		exit(1);
	}

	int line=0;
	char ch;
	while((ch=fgetc(file))!=EOF){
		if(ch=='\n'){
			line++;
		}
	}
	fclose(file);
	printf("child 1 : total no of line %d \n",line);

}

void count_char(const char *filename){
	FILE *file =fopen(filename,"r");
	if(file==NULL){
		perror("failed to open the file\n");
		exit(1);

	}

	int char1=0;
	char ch;
	while((ch=fgetc(file))!=EOF){
		if(ch != ' ' && ch != '\n' && ch != '\t'){
			char1++;
		}
	}
	fclose(file);
	printf("child 2: total number of char %d \n",char1);
}

int main(int argc , char *argv[]){
	if (argc!=2){
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
	}
	pid_t pid1 ,pid2;
	pid1 = fork();
    if (pid1 < 0) {
        perror("Failed to fork first child");
        return 1;
    } else if (pid1 == 0) {
        count_lines(argv[1]);
        exit(0);
    }

    pid2=fork();
    if(pid2<0){
    	perror("failed to fork first child\n");
    	return 1;
    }
    else if(pid2==0){
    	count_char(argv[1]);
    	exit(0);
    }
    wait(NULL); // Wait for the first child
    wait(NULL); // Wait for the second child

    printf("Parent: Both child processes completed.\n");

    return 0;

}