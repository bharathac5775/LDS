#include <stdio.h>
#include <stdlib.h>
typedef struct node *NODE;
typedef struct node {
    int data;
    NODE link;
}node;


NODE createnode(int data) {
    NODE newnode = (NODE)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->link = NULL;
    return newnode;
}


void insert(NODE *head, int data) {
    NODE newnode = createnode(data);
    if (*head == NULL) {
        *head = newnode;
    } else {
        NODE temp = *head;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = newnode;
    }
}

NODE merge_sort_list(NODE A,NODE B){
    NODE C=NULL;

    if(A==NULL)return B;
    if(B==NULL)return A;

    if(A->data<=B->data){
        C=A;
        C->link=merge_sort_list(A->link,B);
    }
    else{
        C=B;
        C->link=merge_sort_list(A,B->link);
    }
    return C;
}

void display(NODE head) {
    while (head != NULL) {
        printf("%d->", head->data);
        head = head->link;
    }
    printf("NULL\n");
}


int main() {
    NODE firstA = NULL;
    NODE firstB = NULL;


    insert(&firstA, 22);
    insert(&firstA, 25);
    insert(&firstA, 70);

    printf("Linked list A: ");
    display(firstA);

    insert(&firstB, 20);
    insert(&firstB, 45);
    insert(&firstB, 60);

    printf("Linked list B: ");
    display(firstB);

    NODE mergc=merge_sort_list(firstA,firstB);
    printf("merged sorted linked list is :\n");
    display(mergc);

    return 0;
}