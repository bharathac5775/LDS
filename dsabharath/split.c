#include <stdio.h> 

#include <stdlib.h> 

 

typedef struct node *list_ptr; 

typedef struct node { 

    int data; 

    list_ptr link; 

}node; 

 

// Pointers for the linked lists 

list_ptr firstA = NULL;  // Original list A 

list_ptr firstB = NULL;  // First half list B 

list_ptr firstC = NULL;  // Second half list C 

 

// Function to insert a node at the end of the list A 

void insert_node(int ele) { 

    list_ptr new_node = (list_ptr)malloc(sizeof(struct node)); 

    new_node->data = ele; 

    new_node->link = NULL; 

 

    if (firstA == NULL) { 

        firstA = new_node; 

        return; 

    } 

 

    list_ptr temp = firstA; 

    while (temp->link != NULL) { 

        temp = temp->link; 

    } 

    temp->link = new_node; 

} 

 

// Function to split the list A into two halves B and C 

void split_list() { 

    if (firstA == NULL || firstA->link == NULL) { 

        // If list A is empty or has only one node 

        firstB = firstA; 

        firstC = NULL; 

        return; 

    } 

 

    list_ptr slow = firstA; 

    list_ptr fast = firstA->link; 

 

    // Using slow and fast pointer to find the midpoint 

    while (fast != NULL && fast->link != NULL) { 

        slow = slow->link; 

        fast = fast->link->link; 

    } 

 

    // Split the list 

    firstB = firstA;          // First half starts from the beginning of A 

    firstC = slow->link;      // Second half starts from the node after slow 

    slow->link = NULL;        // Terminate the first half 

} 

 

// Function to display the list 

void display_list(list_ptr first) { 

    list_ptr temp = first; 

    if (first == NULL) { 

        printf("Empty list\n"); 

        return; 

    } 

 

    while (temp != NULL) { 

        printf("%d -> ", temp->data); 

        temp = temp->link; 

    } 

    printf("NULL\n"); 

} 

 

int main() { 

    int N, ele; 

 

    printf("Enter the number of elements (N): "); 

    scanf("%d", &N); 

 

    // Insert N elements into the list A 

    for (int i = 0; i < N; i++) { 

        printf("Enter element %d: ", i + 1); 

        scanf("%d", &ele); 

        insert_node(ele); 

    } 

 

    printf("\nThe linked list A contents:\n"); 

    display_list(firstA); 

 

    // Split the list after inserting all N elements 

    split_list(); 

 

    // Display the split lists B and C 

    printf("\nFirst half list B:\n"); 

    display_list(firstB); 

    printf("\nSecond half list C:\n"); 

    display_list(firstC); 

 

    return 0; 

} 