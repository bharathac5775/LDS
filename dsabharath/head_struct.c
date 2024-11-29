#include <stdio.h> 

#include <stdlib.h> 

 

typedef struct node *list_ptr; 

typedef struct node { 

    int data; 

    list_ptr link; 

}node; 

 

typedef struct { 

    list_ptr head_ptr; 

    int num; 

} Head; 

 

Head head = {NULL, 0}; 

 

 

list_ptr create_node(int data) { 

    list_ptr new_node = (list_ptr)malloc(sizeof(struct node)); 

    new_node->data = data; 

    new_node->link = NULL; 

    return new_node; 

} 

 

 

void insert_node(int ele) { 

    list_ptr new_node = create_node(ele); 

 

    if (head.head_ptr == NULL) { 

        head.head_ptr = new_node; 

    } else { 

        list_ptr temp = head.head_ptr; 

        while (temp->link != NULL) { 

            temp = temp->link; 

        } 

        temp->link = new_node; 

    } 

    head.num++; 

} 

 

void delete_node(int pos) { 

    if (pos < 1 || pos > head.num) { 

        printf("Invalid position!\n"); 

        return; 

    } 

 

    list_ptr temp = head.head_ptr, prev = NULL; 

 

 

    if (pos == 1) { 

        head.head_ptr = head.head_ptr->link; 

        free(temp); 

    } else { 

 

        for (int i = 1; i < pos; i++) { 

            prev = temp; 

            temp = temp->link; 

        } 

        prev->link = temp->link; 

        free(temp); 

    } 

    head.num--; 

} 

 

void display_list() { 

    if (head.head_ptr == NULL) { 

        printf("The list is empty.\n"); 

        return; 

    } 

 

    list_ptr temp = head.head_ptr; 

    printf("The linked list contents (Count = %d):\n", head.num); 

    while (temp != NULL) { 

        printf("%d->", temp->data); 

        temp = temp->link; 

    } 

    printf("NULL\n"); 

    printf("\n"); 

} 

 

int main() { 

    int ele, pos, ch; 

 

    while (1) { 

        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter your choice: "); 

        scanf("%d", &ch); 

        switch (ch) { 

            case 1: 

                printf("Enter the element to insert: "); 

                scanf("%d", &ele); 

                insert_node(ele); 

                display_list(); 

                break; 

            case 2: 

                printf("Enter the position to delete: "); 

                scanf("%d", &pos); 

                delete_node(pos); 

                display_list(); 

                break; 

            case 3: 

                display_list(); 

                break; 

            case 4: 

                exit(0); 

            default: 

                printf("Invalid choice...\n"); 

                break; 

        } 

    } 

    return 0; 

} 
 