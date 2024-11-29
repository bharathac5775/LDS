#include <stdio.h> 

#include <stdlib.h> 

 

#define MAX_SIZE 100 // Maximum size of the heap 

 

typedef struct { 

    int arr[MAX_SIZE]; // Array to store heap elements 

    int size;          // Current size of the heap 

} MaxHeap; 

 

// Function to initialize the heap 

void initHeap(MaxHeap* heap) { 

    heap->size = 0; 

} 

 

// Function to swap two elements 

void swap(int* a, int* b) { 

    int temp = *a; 

    *a = *b; 

    *b = temp; 

} 

 

// Function to insert an element into the Max Heap 

void insert(MaxHeap* heap, int key) { 

    if (heap->size == MAX_SIZE) { 

        printf("Heap is full, cannot insert %d\n", key); 

        return; 

    } 

 

    // Insert the new element at the end 

    int index = heap->size; 

    heap->arr[index] = key; 

    heap->size++; 

 

    // Heapify the inserted element to maintain the Max Heap property 

    while (index != 0 && heap->arr[index] > heap->arr[(index - 1) / 2]) { 

        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]); 

        index = (index - 1) / 2; 

    } 

} 

 

// Function to extract the maximum element from the Max Heap 

int extractMax(MaxHeap* heap) { 

    if (heap->size <= 0) { 

        printf("Heap is empty, cannot extract maximum\n"); 

        return -1; // Return -1 if heap is empty 

    } 

 

    if (heap->size == 1) { 

        heap->size--; 

        return heap->arr[0]; 

    } 

 

    // Store the maximum value 

    int root = heap->arr[0]; 

    heap->arr[0] = heap->arr[heap->size - 1]; // Move the last element to root 

    heap->size--; 

 

    // Heapify the root element to maintain the Max Heap property 

    int index = 0; 

    while (index < heap->size) { 

        int largest = index; 

        int leftChild = 2 * index + 1; 

        int rightChild = 2 * index + 2; 

 

        if (leftChild < heap->size && heap->arr[leftChild] > heap->arr[largest]) { 

            largest = leftChild; 

        } 

 

        if (rightChild < heap->size && heap->arr[rightChild] > heap->arr[largest]) { 

            largest = rightChild; 

        } 

 

        if (largest != index) { 

            swap(&heap->arr[index], &heap->arr[largest]); 

            index = largest; 

        } else { 

            break; // No need to continue if the heap property is satisfied 

        } 

    } 

 

    return root; 

} 

 

// Function to print the heap 

void printHeap(MaxHeap* heap) { 

    for (int i = 0; i < heap->size; i++) { 

        printf("%d ", heap->arr[i]); 

    } 

    printf("\n"); 

} 

 

// Main function 

int main() { 

    MaxHeap heap; 

    initHeap(&heap); 

 

    int choice, value; 

 

    while (1) { 

        printf("Menu:\n"); 

        printf("1. Insert element into heap\n"); 

        printf("2. Extract maximum element from heap\n"); 

        printf("3. Print heap\n"); 

        printf("4. Exit\n"); 

        printf("Enter your choice: "); 

        scanf("%d", &choice); 

        switch (choice) { 

            case 1: 

                printf("Enter the element to insert: "); 

                scanf("%d", &value); 

                insert(&heap, value); 

                break; 

            case 2: 

                value = extractMax(&heap); 

                if (value != -1) { 

                    printf("Extracted maximum element: %d\n", value); 

                } 

                break; 

            case 3: 

                printf("Heap elements: "); 

                printHeap(&heap); 

                break; 

            case 4: 

                exit(0); 

            default: 

                printf("Invalid choice. Please try again.\n"); 

        } 

    } 

return 0; 

    } 