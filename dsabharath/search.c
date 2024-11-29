#include <stdio.h> 

 

void linear_search(int arr[], int n, int target) { 

    int found = 0; 

    for (int i = 0; i < n; i++) { 

        if (arr[i] == target) { 

            printf("Element %d found at index %d.\n", target, i); 

            found = 1; 

            break; 

        } 

    } 

    if (!found) { 

        printf("Element %d not found in the array.\n", target); 

    } 

} 

 

void bubble_sort(int arr[], int n) {  // Helper function for Binary Search 

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

 

void binary_search(int arr[], int n, int target) { 

    int left = 0, right = n - 1, found = 0; 

    bubble_sort(arr, n); // Ensure array is sorted 

 

    while (left <= right) { 

        int mid = (left + right) / 2; 

        if (arr[mid] == target) { 

            printf("Element %d found at index %d.\n", target, mid); 

            found = 1; 

            break; 

        } else if (arr[mid] < target) { 

            left = mid + 1; 

        } else { 

            right = mid - 1; 

        } 

    } 

    if (!found) { 

        printf("Element %d not found in the array.\n", target); 

    } 

} 

 

int main() { 

    int arr[] = {64, 34, 25, 12, 22, 11, 90}; 

    int n = sizeof(arr) / sizeof(arr[0]); 

    int choice, target; 

 

    while (1) { 

        printf("\nSelect a search option:\n"); 

        printf("1. Linear Search\n"); 

        printf("2. Binary Search\n"); 

        printf("3. Exit\n"); 

        printf("Enter your choice: "); 

        scanf("%d", &choice); 

 

        if (choice == 3) break; 

 

        printf("Enter the element to search: "); 

        scanf("%d", &target); 

 

        switch (choice) { 

            case 1: 

                linear_search(arr, n, target); 

                break; 

            case 2: 

                binary_search(arr, n, target); 

                break; 

            default: 

                printf("Invalid choice! Please select again.\n"); 

                break; 

        } 

    } 

    return 0; 

} 