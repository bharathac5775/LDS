#include<stdio.h>
#include<pthread.h>

void* first_thread_function(void* arg){
	printf("this is thread one\n");
	return NULL;
}

void* second_thread_function(void* arg){
	printf("this is thread two\n");
	return NULL;
}
int main(){
	pthread_t thread1,thread2;

	if(pthread_create(&thread1,NULL,first_thread_function,NULL)!=0){
		perror("failed to create thread one\n");
		return 1;
	}
	if(pthread_create(&thread2,NULL,second_thread_function,NULL)!=0){
		perror("failed to create thread two\n");
		return 1;
    }

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("both thread exicuted\n");
    return 0;
}