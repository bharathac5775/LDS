#include <stdio.h> 

#include <stdbool.h> 

 

// Function to perform insertion sort on an array 

void insertionSort(int arr[], int n) { 

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

 

// Function to check if there exists a pair with a given sum x 

bool hasPairWithSum(int arr[], int n, int x) { 

    insertionSort(arr, n); // Sort the array in O(n log n) 

 

    int left = 0; 

    int right = n - 1; 

 

    while (left < right) { 

        int sum = arr[left] + arr[right]; 

 

        if (sum == x) { 

            printf("Pair found: %d and %d\n", arr[left], arr[right]); 

            return true; 

        } else if (sum < x) { 

            left++; // Move left pointer to the right to increase sum 

        } else { 

            right--; // Move right pointer to the left to decrease sum 

        } 

    } 

    return false; 

} 

 

int main() { 

    int n, x; 

 

    // Input array size 

    printf("Enter the number of elements: "); 

    scanf("%d", &n); 

 

    int arr[n]; 

 

    // Input array elements 

    printf("Enter the elements of the array:\n"); 

    for (int i = 0; i < n; i++) { 

        scanf("%d", &arr[i]); 

    } 

 

    // Input the sum to find 

    printf("Enter the sum to find: "); 

    scanf("%d", &x); 

 

    // Check for the pair with given sum 

    if (!hasPairWithSum(arr, n, x)) { 

        printf("No pair with the given sum found.\n"); 

    } 

 

    return 0; 

} 