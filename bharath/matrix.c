#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10  // Max number of rows or columns for simplicity

// Global matrix and row sum array
int matrix[MAX][MAX];
int row_sums[MAX];

// Structure to pass row index to thread
typedef struct {
    int row;
} ThreadData;

// Function to calculate the sum of the row
void* calculate_row_sum(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;
    int sum = 0;
    
    // Calculate sum of the ith row
    for (int j = 0; j < MAX; j++) {
        sum += matrix[row][j];
    }
    
    // Store the result in the global row_sums array
    row_sums[row] = sum;
    
    return NULL;
}

// Function to generate a random matrix
void generate_matrix(int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10 + 1;  // Random values between 1 and 10
        }
    }
}

// Function to display the matrix
void display_matrix(int m, int n) {
    printf("Matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display row sums
void display_row_sums(int m) {
    printf("Row sums:\n");
    int total_sum = 0;
    for (int i = 0; i < m; i++) {
        printf("Row %d sum: %d\n", i, row_sums[i]);
        total_sum += row_sums[i];
    }
    printf("Total sum: %d\n", total_sum);
}

int main() {
    int m, n;

    // Read dimensions of the matrix
    printf("Enter the number of rows (m): ");
    scanf("%d", &m);
    printf("Enter the number of columns (n): ");
    scanf("%d", &n);

    // Generate the matrix
    generate_matrix(m, n);

    // Display the generated matrix
    display_matrix(m, n);

    // Array of thread identifiers
    pthread_t threads[m];

    // Create m threads to calculate each row sum
    for (int i = 0; i < m; i++) {
        ThreadData* data = (ThreadData*) malloc(sizeof(ThreadData));
        data->row = i;
        if (pthread_create(&threads[i], NULL, calculate_row_sum, (void*)data) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the row sums and total sum
    display_row_sums(m);

    return 0;
}
