#include <stdio.h> 

#include <stdlib.h> 

 

// Define the structure for a node in the binary tree 

struct Node { 

    int data; 

    struct Node* left; 

    struct Node* right; 

}; 

 

// Function to create a new node 

struct Node* createNode(int data) { 

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 

    newNode->data = data; 

    newNode->left = NULL; 

    newNode->right = NULL; 

    return newNode; 

} 

 

// Insert a node in the binary tree 

struct Node* insertNode(struct Node* root, int data) { 

    if (root == NULL) { 

        root = createNode(data); 

    } else { 

        if (data < root->data) { 

            root->left = insertNode(root->left, data); 

        } else { 

            root->right = insertNode(root->right, data); 

        } 

    } 

    return root; 

} 

 

// Inorder traversal: Left, Root, Right 

void inorderTraversal(struct Node* root) { 

    if (root == NULL) return; 

 

    inorderTraversal(root->left); 

    printf("%d ", root->data); 

    inorderTraversal(root->right); 

} 

 

// Preorder traversal: Root, Left, Right 

void preorderTraversal(struct Node* root) { 

    if (root == NULL) return; 

 

    printf("%d ", root->data); 

    preorderTraversal(root->left); 

    preorderTraversal(root->right); 

} 

 

// Postorder traversal: Left, Right, Root 

void postorderTraversal(struct Node* root) { 

    if (root == NULL) return; 

 

    postorderTraversal(root->left); 

    postorderTraversal(root->right); 

    printf("%d ", root->data); 

} 

 

int main() { 

    struct Node* root = NULL; 

    int choice, data; 

 

    // Build the binary tree 

    while (1) { 

        printf("\n1. Insert Node\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n5. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

 

        switch (choice) { 

            case 1: 

                printf("Enter data to insert: "); 

                scanf("%d", &data); 

                root = insertNode(root, data); 

                break; 

            case 2: 

                printf("Inorder Traversal: "); 

                inorderTraversal(root); 

                printf("\n"); 

                break; 

            case 3: 

                printf("Preorder Traversal: "); 

                preorderTraversal(root); 

                printf("\n"); 

                break; 

            case 4: 

                printf("Postorder Traversal: "); 

                postorderTraversal(root); 

                printf("\n"); 

                break; 

            case 5: 

                exit(0); 

            default: 

                printf("Invalid choice.\n"); 

        } 

    } 

 

    return 0; 

} 