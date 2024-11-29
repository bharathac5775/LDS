#include <stdio.h> 

#include <stdlib.h> 

 

// Sorting Functions 

 

// Bubble Sort 

void bubble_sort(int arr[], int n) { 

    for (int i = 0; i < n - 1; i++) { 

        for (int j = 0; j < n - i - 1; j++) { 

            if (arr[j] > arr[j + 1]) { 

                int temp = arr[j]; 

                arr[j] = arr[j + 1]; 

                arr[j + 1] = temp; 

            } 

        } 

    } 

} 

 

// Selection Sort 

void selection_sort(int arr[], int n) { 

    for (int i = 0; i < n - 1; i++) { 

        int mini = i; 

        for (int j = i + 1; j < n; j++) { 

            if (arr[j] < arr[mini]) { 

                mini = j; 

            } 

        } 

        int temp = arr[mini]; 

        arr[mini] = arr[i]; 

        arr[i] = temp; 

    } 

} 

 

// Insertion Sort 

void insertion_sort(int arr[], int n) { 

    for (int i = 1; i < n; i++) { 

        int key = arr[i]; 

        int j = i - 1; 

        while (j >= 0 && arr[j] > key) { 

            arr[j + 1] = arr[j]; 

            j--; 

        } 

        arr[j + 1] = key; 

    } 

} 

 

// Quick Sort Helper - Partition 

int partition(int arr[], int low, int high) { 

    int pivot = arr[low]; 

    int i = low; 

    int j = high; 

    while (i < j) { 

        while (arr[i] <= pivot && i < high) i++; 

        while (arr[j] > pivot && j > low) j--; 

        if (i < j) { 

            int temp = arr[i]; 

            arr[i] = arr[j]; 

            arr[j] = temp; 

        } 

    } 

    int temp = arr[low]; 

    arr[low] = arr[j]; 

    arr[j] = temp; 

    return j; 

} 

 

// Quick Sort 

void quick_sort(int arr[], int low, int high) { 

    if (low < high) { 

        int pIndex = partition(arr, low, high); 

        quick_sort(arr, low, pIndex - 1); 

        quick_sort(arr, pIndex + 1, high); 

    } 

} 

 

// Merge Sort Helper - Merge 

void merge(int arr[], int low, int mid, int high) { 

    int n = high - low + 1; 

    int temp[n]; 

    int left = low, right = mid + 1, k = 0; 

    while (left <= mid && right <= high) { 

        if (arr[left] <= arr[right]) { 

            temp[k++] = arr[left++]; 

        } else { 

            temp[k++] = arr[right++]; 

        } 

    } 

    while (left <= mid) temp[k++] = arr[left++]; 

    while (right <= high) temp[k++] = arr[right++]; 

    for (int i = low, j = 0; i <= high; i++, j++) { 

        arr[i] = temp[j]; 

    } 

} 

 

// Merge Sort 

void merge_sort(int arr[], int low, int high) { 

    if (low < high) { 

        int mid = (low + high) / 2; 

        merge_sort(arr, low, mid); 

        merge_sort(arr, mid + 1, high); 

        merge(arr, low, mid, high); 

    } 

} 

 

// Heapify Function (using provided logic) 

void heapify(int H[], int n) { 

    for (int i = n / 2; i >= 1; i--) { 

        int k = i; 

        int v = H[k]; 

        int heap = 0; 

        while (!heap && (2 * k) <= n) { 

            int j = 2 * k; 

            if (j < n && H[j] < H[j + 1]) j++; 

            if (v >= H[j]) { 

                heap = 1; 

            } else { 

                H[k] = H[j]; 

                k = j; 

            } 

        } 

        H[k] = v; 

    } 

} 

 

// Heap Sort (using provided logic) 

void heap_sort(int H[], int n) { 

    // Adjusting index to use 1-based index in H 

    int i; 

    H--;  // Offset array for 1-based indexing 

    heapify(H, n); 

    for (i = n; i >= 2; i--) { 

        // Swap without using temp variable 

        H[1] = H[1] + H[i]; 

        H[i] = H[1] - H[i]; 

        H[1] = H[1] - H[i]; 

        heapify(H, i - 1); 

    } 

    H++;  // Restore original indexing 

} 

 

// Utility function to print the array 

void print_array(int arr[], int n) { 

    for (int i = 0; i < n; i++) { 

        printf("%d ", arr[i]); 

    } 

    printf("\n"); 

} 

 

// Function to reset array to original values 

void reset_array(int arr[], int original[], int n) { 

    for (int i = 0; i < n; i++) { 

        arr[i] = original[i]; 

    } 

} 

 

// Main function 

int main() { 

    int arr[] = {64, 25, 12, 22, 11}; 

    int original[] = {64, 25, 12, 22, 11}; // Original array for resetting 

    int n = sizeof(arr) / sizeof(arr[0]); 

    int choice; 

 

    do { 

        printf("\nArray Sorting Menu:\n"); 

        printf("1. Bubble Sort\n"); 

        printf("2. Selection Sort\n"); 

        printf("3. Insertion Sort\n"); 

        printf("4. Quick Sort\n"); 

        printf("5. Merge Sort\n"); 

        printf("6. Heap Sort\n"); 

        printf("7. Exit\n"); 

        printf("Enter your choice: "); 

        scanf("%d", &choice); 

 

        // Reset array before each sorting technique 

        reset_array(arr, original, n); 

 

        switch (choice) { 

            case 1: 

                bubble_sort(arr, n); 

                printf("Bubble Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 2: 

                selection_sort(arr, n); 

                printf("Selection Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 3: 

                insertion_sort(arr, n); 

                printf("Insertion Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 4: 

                quick_sort(arr, 0, n - 1); 

                printf("Quick Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 5: 

                merge_sort(arr, 0, n - 1); 

                printf("Merge Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 6: 

                heap_sort(arr, n); 

                printf("Heap Sorted array: "); 

                print_array(arr, n); 

                break; 

            case 7: 

                printf("Exiting the program.\n"); 

                break; 

            default: 

                printf("Invalid choice! Please choose again.\n"); 

        } 

    } while (choice != 7); 

 

    return 0; 

} 