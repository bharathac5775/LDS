#include <stdio.h> 

#include <stdlib.h> 

#define MAX 10 

 

typedef struct Queue{ 

    int item[MAX]; 

    int front ,rear; 

}Queue; 

 

Queue q1,q2; 

 

void initQueue(Queue *q){ 

    q->front=-1; 

    q->rear=-1; 

} 

 

int isempty(Queue *q){ 

    return(q->front==-1); 

} 

 

int isfull(Queue *q){ 

    return(q->rear==MAX-1); 

} 

 

void enqueue(Queue *q,int ele){ 

    if(isfull(q)){ 

        printf("queue is full\n"); 

        return; 

    } 

    if(isempty(q)){ 

        q->front=0; 

    } 

    q->rear++; 

    q->item[q->rear]=ele; 

} 

 

int dequeue(Queue *q){ 

    if(isempty(q)){ 

        printf("queue is empty\n"); 

        return; 

    } 

    int item = q->item[q->front]; 

 

    if(q->front==q->rear){ 

        q->front=q->rear=-1; 

    } 

    else{ 

        q->front++; 

    } 

    return item; 

} 

 

void push(int ele){ 

    enqueue(&q2,ele); 

    while(!isempty(&q1)){ 

        int item=dequeue(&q1); 

        enqueue(&q2,item); 

    } 

    Queue temp=q1; 

    q1=q2; 

    q2=temp; 

} 

 

int pop() { 

    if (isempty(&q1)) { 

        printf("Stack is empty\n"); 

        return -1; 

    } 

    return dequeue(&q1); 

} 

 

void display() { 

    if (isempty(&q1)) { 

        printf("Stack is empty\n"); 

        return; 

    } 

    printf("Stack elements: "); 

    for (int i = q1.front; i <= q1.rear; i++) { 

        printf("%d ", q1.item[i]); 

    } 

    printf("\n"); 

} 

 

int main() 

{ 

    initQueue(&q1); 

    initQueue(&q2); 

 

    int choice, value; 

    while (1) { 

        printf("\nChoose an operation:\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

 

        switch (choice) { 

            case 1: 

                printf("Enter value to push: "); 

                scanf("%d", &value); 

                push(value); 

                break; 

            case 2: 

                value = pop(); 

                if (value != -1) 

                    printf("Popped element: %d\n", value); 

                break; 

            case 3: 

                display(); 

                break; 

            case 4: 

                exit(0); 

            default: 

                printf("Invalid choice\n"); 

        } 

    } 

    return 0; 

} 