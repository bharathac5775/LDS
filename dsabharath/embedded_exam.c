#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *list_ptr;

typedef struct node {
    int data;
    list_ptr link;
} node;

list_ptr first = NULL;

// Function to create nodes
void create_node(int n) {
    list_ptr new_node;
    int i, ele;
    printf("Enter the node values:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &ele);
        new_node = (list_ptr)malloc(sizeof(node));
        new_node->data = ele;
        new_node->link = first;
        first = new_node;
    }
}

// Function to count nodes in the list
int count_nodes() {
    int count = 0;
    list_ptr temp = first;
    while (temp != NULL) {
        count++;
        temp = temp->link;
    }
    return count;
}

// Function to delete a node at a specific position
void delete_node(int pos) {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }

    list_ptr temp = first, prev = NULL;
    if (pos == 1) {  // Delete the first node
        first = first->link;
        free(temp);
        return;
    }

    for (int i = 1; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->link;
    }

    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return;
    }

    prev->link = temp->link;
    free(temp);
}

// Function to display the list
void display_list() {
    list_ptr temp = first;
    if (first == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("The linked list contents:\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

// Main function
int main() {
    int n;

    printf("Enter the number of nodes to create: ");
    scanf("%d", &n);
    create_node(n);

    while (1) {
        int node_count = count_nodes();
        if (node_count == 0) {
            printf("No nodes left to delete.\n");
            break;
        }

        // Generate a random position between 1 and node_count
        srand(time(0));
        int pos = (rand() % node_count) + 1;
        printf("Randomly selected position to delete: %d\n", pos);

        delete_node(pos);
        display_list();

        char choice;
        printf("Do you want to delete another node? (y/n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}
