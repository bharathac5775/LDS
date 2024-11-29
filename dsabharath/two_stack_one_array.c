#include <stdio.h> 

#include <stdlib.h> 

#define N 10 

 

int A[N]; 

int top1 = -1; 

int top2 = N; 

 

void push1(int ele) { 

    if (top1 < top2 - 1) { 

        top1++; 

        A[top1] = ele; 

    } else { 

        printf("Stack Overflow for Stack 1\n"); 

    } 

} 

 

void push2(int ele) { 

    if (top2 > top1 + 1) { 

        top2--; 

        A[top2] = ele; 

    } else { 

        printf("Stack Overflow for Stack 2\n"); 

    } 

} 

 

int pop1() { 

    if (top1 >= 0) { 

        int ele = A[top1]; 

        top1--; 

        return ele; 

    } else { 

        printf("Stack 1 is empty\n"); 

        return -1; 

    } 

} 

 

int pop2() { 

    if (top2 < N) { 

        int ele = A[top2]; 

        top2++; 

        return ele; 

    } else { 

        printf("Stack 2 is empty\n"); 

        return -1; 

    } 

} 

 

void display_stack1() { 

    if (top1 == -1) { 

        printf("Stack 1 is empty\n"); 

        return; 

    } 

    printf("Stack 1 elements: "); 

    for (int i = 0; i <= top1; i++) { 

        printf("%d ", A[i]); 

    } 

    printf("\n"); 

} 

 

void display_stack2() { 

    if (top2 == N) { 

        printf("Stack 2 is empty\n"); 

        return; 

    } 

    printf("Stack 2 elements: "); 

    for (int i = N - 1; i >= top2; i--) { 

        printf("%d ", A[i]); 

    } 

    printf("\n"); 

} 

 

int main() { 

    int ch, ele, stack_num; 

 

    while (1) { 

        printf("\nChoose stack and operation:\n"); 

        printf("1. Push to Stack 1\n2. Push to Stack 2\n"); 

        printf("3. Pop from Stack 1\n4. Pop from Stack 2\n"); 

        printf("5. Display Stack 1\n6. Display Stack 2\n7. Exit\n"); 

        printf("Enter your choice: "); 

        scanf("%d", &ch); 

 

        switch (ch) { 

            case 1: 

                printf("Enter the element to push to Stack 1: "); 

                scanf("%d", &ele); 

                push1(ele); 

                break; 

            case 2: 

                printf("Enter the element to push to Stack 2: "); 

                scanf("%d", &ele); 

                push2(ele); 

                break; 

            case 3: 

                ele = pop1(); 

                if (ele != -1) 

                    printf("Popped element from Stack 1: %d\n", ele); 

                break; 

            case 4: 

                ele = pop2(); 

                if (ele != -1) 

                    printf("Popped element from Stack 2: %d\n", ele); 

                break; 

            case 5: 

                display_stack1(); 

                break; 

            case 6: 

                display_stack2(); 

                break; 

            case 7: 

                exit(0); 

            default: 

                printf("Invalid choice\n"); 

        } 

    } 

    return 0; 

} 