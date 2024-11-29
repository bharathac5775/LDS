#include <stdio.h> 

#include <stdlib.h> 

 

void swap(int *a, int *b) { 

    int temp = *a; 

    *a = *b; 

    *b = temp; 

} 

 

// Function to heapify a subtree rooted at index i for a Max-Heap 

void maxHeapify(int arr[], int n, int i) { 

    int largest = i;       // Initialize largest as root 

    int left = 2 * i + 1;  // Left child index 

    int right = 2 * i + 2; // Right child index 

 

    // If left child is larger than root 

    if (left < n && arr[left] > arr[largest]) { 

        largest = left; 

    } 

 

    // If right child is larger than largest so far 

    if (right < n && arr[right] > arr[largest]) { 

        largest = right; 

    } 

 

    // If largest is not root, swap and continue heapifying 

    if (largest != i) { 

        swap(&arr[i], &arr[largest]); 

        maxHeapify(arr, n, largest); 

    } 

} 

 

// Function to convert a Min-Heap to a Max-Heap 

void convertMinHeapToMaxHeap(int arr[], int n) { 

    // Start from the last non-leaf node and heapify each node in reverse order 

    for (int i = (n / 2) - 1; i >= 0; i--) { 

        maxHeapify(arr, n, i); 

    } 

} 

 

// Function to print an array (Heap) 

void printHeap(int arr[], int n) { 

    for (int i = 0; i < n; i++) { 

        printf("%d ", arr[i]); 

    } 

    printf("\n"); 

} 

 

int main() { 

    // Example Min-Heap array representation 

    int minHeap[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; 

    int n = sizeof(minHeap) / sizeof(minHeap[0]); 

 

    printf("Original Min-Heap: "); 

    printHeap(minHeap, n); 

 

    // Convert Min-Heap to Max-Heap 

    convertMinHeapToMaxHeap(minHeap, n); 

 

    printf("Converted Max-Heap: "); 

    printHeap(minHeap, n); 

 

    return 0; 

} 