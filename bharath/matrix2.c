#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m; // n = number of processes, m = number of resource types
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int work[MAX_RESOURCES];
bool finish[MAX_PROCESSES];

// Function to calculate the Need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if a process can be completed
bool isProcessSafe(int p) {
    for (int i = 0; i < m; i++) {
        if (need[p][i] > work[i]) {
            return false; // Process cannot be completed
        }
    }
    return true;
}

// Function to implement the Banker's Algorithm for safety check
bool bankersAlgorithm() {
    calculateNeed();

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int count = 0; // Count the number of processes that can finish
    while (count < n) {
        bool progressMade = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p] && isProcessSafe(p)) {
                // Simulate the allocation of resources
                for (int i = 0; i < m; i++) {
                    work[i] += allocation[p][i];
                }
                finish[p] = true;
                count++;
                printf("Process P%d can finish. Resources allocated, new Work: ", p);
                for (int i = 0; i < m; i++) {
                    printf("%d ", work[i]);
                }
                printf("\n");
                progressMade = true;
                break;
            }
        }
        if (!progressMade) {
            printf("System is in an unsafe state. No process can proceed.\n");
            return false;
        }
    }
    return true; // System is in a safe state
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    printf("Enter the Available vector: \n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the Max matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Initialize Work vector
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Run the Banker's Algorithm
    if (bankersAlgorithm()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}
