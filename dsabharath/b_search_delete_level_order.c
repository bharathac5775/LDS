#include <stdio.h> 

#include <stdlib.h> 

 

// Define structure for a node in the BST 

struct Node { 

    int data; 

    struct Node* left; 

    struct Node* right; 

}; 

 

// Queue node structure for level order traversal 

struct QueueNode { 

    struct Node* treeNode; 

    struct QueueNode* next; 

}; 

 

// Function to create a new node in the BST 

struct Node* createNode(int data) { 

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 

    newNode->data = data; 

    newNode->left = NULL; 

    newNode->right = NULL; 

    return newNode; 

} 

 

// Insert a node in the BST 

struct Node* insertNode(struct Node* root, int data) { 

    if (root == NULL) { 

        return createNode(data); 

    } 

    if (data < root->data) { 

        root->left = insertNode(root->left, data); 

    } else if (data > root->data) { 

        root->right = insertNode(root->right, data); 

    } 

    return root; 

} 

 

// Find the minimum value node in the BST 

struct Node* findMinNode(struct Node* root) { 

    struct Node* current = root; 

    while (current && current->left != NULL) { 

        current = current->left; 

    } 

    return current; 

} 

 

// Delete a node in the BST 

struct Node* deleteNode(struct Node* root, int data) { 

    if (root == NULL) return root; 

 

    if (data < root->data) { 

        root->left = deleteNode(root->left, data); 

    } else if (data > root->data) { 

        root->right = deleteNode(root->right, data); 

    } else { 

        // Node with one or no child 

        if (root->left == NULL) { 

            struct Node* temp = root->right; 

            free(root); 

            return temp; 

        } else if (root->right == NULL) { 

            struct Node* temp = root->left; 

            free(root); 

            return temp; 

        } 

         

        // Node with two children: get inorder successor (smallest in the right subtree) 

        struct Node* temp = findMinNode(root->right); 

        root->data = temp->data; 

        root->right = deleteNode(root->right, temp->data); 

    } 

    return root; 

} 

 

// Queue functions for Level Order Traversal 

struct QueueNode* createQueueNode(struct Node* treeNode) { 

    struct QueueNode* newQueueNode = (struct QueueNode*)malloc(sizeof(struct QueueNode)); 

    newQueueNode->treeNode = treeNode; 

    newQueueNode->next = NULL; 

    return newQueueNode; 

} 

 

void enqueue(struct QueueNode** front, struct QueueNode** rear, struct Node* treeNode) { 

    struct QueueNode* newQueueNode = createQueueNode(treeNode); 

    if (*rear == NULL) { 

        *front = *rear = newQueueNode; 

    } else { 

        (*rear)->next = newQueueNode; 

        *rear = newQueueNode; 

    } 

} 

 

struct Node* dequeue(struct QueueNode** front, struct QueueNode** rear) { 

    if (*front == NULL) return NULL; 

    struct Node* treeNode = (*front)->treeNode; 

    struct QueueNode* temp = *front; 

    *front = (*front)->next; 

    if (*front == NULL) *rear = NULL; 

    free(temp); 

    return treeNode; 

} 

 

// Level Order Traversal (Breadth-First Search) 

void levelOrderTraversal(struct Node* root) { 

    if (root == NULL) return; 

     

    struct QueueNode *front = NULL, *rear = NULL; 

    enqueue(&front, &rear, root); 

     

    printf("Level Order Traversal: "); 

    while (front != NULL) { 

        struct Node* currentNode = dequeue(&front, &rear); 

        printf("%d ", currentNode->data); 

         

        if (currentNode->left != NULL) { 

            enqueue(&front, &rear, currentNode->left); 

        } 

        if (currentNode->right != NULL) { 

            enqueue(&front, &rear, currentNode->right); 

        } 

    } 

    printf("\n"); 

} 

 

int main() { 

    struct Node* root = NULL; 

    int choice, data; 

 

    while (1) { 

        printf("\n1. Insert Node\n2. Delete Node\n3. Level Order Traversal\n4. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

 

        switch (choice) { 

            case 1: 

                printf("Enter data to insert: "); 

                scanf("%d", &data); 

                root = insertNode(root, data); 

                break; 

            case 2: 

                printf("Enter data to delete: "); 

                scanf("%d", &data); 

                root = deleteNode(root, data); 

                break; 

            case 3: 

                levelOrderTraversal(root); 

                break; 

            case 4: 

                exit(0); 

            default: 

                printf("Invalid choice.\n"); 

        } 

    } 

 

    return 0; 

} 