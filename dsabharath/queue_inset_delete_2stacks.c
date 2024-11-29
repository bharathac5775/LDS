#include <stdio.h> 

#include <stdlib.h> 

 

#define MAX 10 

 

typedef struct Stack { 

    int items[MAX]; 

    int top; 

} Stack; 

 

void initStack(Stack *s) { 

    s->top = -1; 

} 

 

int isStackEmpty(Stack *s) { 

    return (s->top == -1); 

} 

 

int isStackFull(Stack *s) { 

    return (s->top == MAX - 1); 

} 

 

void push(Stack *s, int value) { 

    if (isStackFull(s)) { 

        printf("Stack is full\n"); 

        return; 

    } 

    s->items[++s->top] = value; 

} 

 

int pop(Stack *s) { 

    if (isStackEmpty(s)) { 

        printf("Stack is empty\n"); 

        return -1; 

    } 

    return s->items[s->top--]; 

} 

 

Stack stack1, stack2; 

 

void insert(int value) { 

    while (!isStackEmpty(&stack1)) { 

        push(&stack2, pop(&stack1)); 

    } 

 

    push(&stack1, value); 

 

    while (!isStackEmpty(&stack2)) { 

        push(&stack1, pop(&stack2)); 

    } 

} 

 

int delete() { 

    if (isStackEmpty(&stack1)) { 

        printf("Queue is empty\n"); 

        return -1; 

    } 

    return pop(&stack1); 

} 

 

void display() { 

    if (isStackEmpty(&stack1)) { 

        printf("Queue is empty\n"); 

        return; 

    } 

    printf("Queue elements: "); 

    for (int i = 0; i <= stack1.top; i++) { 

        printf("%d ", stack1.items[i]); 

    } 

    printf("\n"); 

} 

 

int main() { 

    initStack(&stack1); 

    initStack(&stack2); 

 

    int choice, value; 

    while (1) { 

        printf("\nChoose an operation:\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

 

        switch (choice) { 

            case 1: 

                printf("Enter value to insert: "); 

                scanf("%d", &value); 

                insert(value); 

                break; 

            case 2: 

                value = delete(); 

                if (value != -1) 

                    printf("Deleted element: %d\n", value); 

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