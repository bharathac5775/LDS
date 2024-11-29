#include <stdio.h> 

 

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

 

void merge_arrays(int arr1[], int n1, int arr2[], int n2, int result[]) { 

    int i = 0, j = 0, k = 0; 

    while (i < n1 && j < n2) { 

        if (arr1[i] <= arr2[j]) { 

            result[k++] = arr1[i++]; 

        } else { 

            result[k++] = arr2[j++]; 

        } 

    } 

    // Copy remaining elements, if any 

    while (i < n1) { 

        result[k++] = arr1[i++]; 

    } 

    while (j < n2) { 

        result[k++] = arr2[j++]; 

    } 

} 

 

int main() { 

    int n1, n2; 

 

    // Take the size and elements of the first array 

    printf("Enter the size of the first array: "); 

    scanf("%d", &n1); 

    int arr1[n1]; 

    printf("Enter %d elements of the first array:\n", n1); 

    for (int i = 0; i < n1; i++) { 

        scanf("%d", &arr1[i]); 

    } 

 

    // Take the size and elements of the second array 

    printf("Enter the size of the second array: "); 

    scanf("%d", &n2); 

    int arr2[n2]; 

    printf("Enter %d elements of the second array:\n", n2); 

    for (int i = 0; i < n2; i++) { 

        scanf("%d", &arr2[i]); 

    } 

 

    // Sort both arrays using insertion sort 

    insertion_sort(arr1, n1); 

    insertion_sort(arr2, n2); 

 

    // Prepare result array and merge sorted arrays into it 

    int result[n1 + n2]; 

    merge_arrays(arr1, n1, arr2, n2, result); 

 

    // Display the resultant merged and sorted array 

    printf("Merged and sorted array:\n"); 

    for (int i = 0; i < n1 + n2; i++) { 

        printf("%d ", result[i]); 

    } 

    printf("\n"); 

 

    return 0; 

} 