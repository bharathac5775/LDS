#include <stdio.h> 

#include <stdlib.h> 

 

// Structure to represent a node in the binary tree 

typedef struct Node { 

    int data; 

    struct Node* left; 

    struct Node* right; 

} Node; 

 

// Function to create a new node 

Node* createNode(int data) { 

    Node* newNode = (Node*)malloc(sizeof(Node)); 

    newNode->data = data; 

    newNode->left = NULL; 

    newNode->right = NULL; 

    return newNode; 

} 

 

// Function to count the number of leaf nodes 

int countLeafNodes(Node* root) { 

    if (root == NULL) { 

        return 0; 

    } 

    if (root->left == NULL && root->right == NULL) { 

        return 1; // It's a leaf node 

    } 

    return countLeafNodes(root->left) + countLeafNodes(root->right); 

} 

 

// Function to count the total number of nodes 

int countTotalNodes(Node* root) { 

    if (root == NULL) { 

        return 0; 

    } 

    return 1 + countTotalNodes(root->left) + countTotalNodes(root->right); 

} 

 

// Function to display all the values of the nodes 

void displayNodeValues(Node* root) { 

    if (root != NULL) { 

        printf("%d ", root->data); 

        displayNodeValues(root->left); 

        displayNodeValues(root->right); 

    } 

} 

 

// Main function to demonstrate the above functions 

int main() { 

    // Creating a sample binary tree 

    Node* root = createNode(1); 

    root->left = createNode(2); 

    root->right = createNode(3); 

    root->left->left = createNode(4); 

    root->left->right = createNode(5); 

    root->right->left = createNode(6); 

    root->right->right = createNode(7); 

 

    // Counting leaf nodes 

    int leafCount = countLeafNodes(root); 

    printf("Number of leaf nodes: %d\n", leafCount); 

 

    // Counting total nodes 

    int totalCount = countTotalNodes(root); 

    printf("Total number of nodes: %d\n", totalCount); 

 

    // Displaying all node values 

    printf("Node values in the tree: "); 

    displayNodeValues(root); 

    printf("\n"); 

 

    return 0; 

} 