#include <stdio.h>

#define MAX_PROCESS 100

// Function to calculate waiting time
void calculateWaitingTime(int n, int burstTime[], int timeSlice, int waitingTime[]) {
    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = burstTime[i];
    }

    int time = 0;
    int i = 0;
    while (1) {
        int done = 1;
        for (int j = 0; j < n; j++) {
            if (remainingBurstTime[j] > 0) {
                done = 0;
                if (remainingBurstTime[j] > timeSlice) {
                    time += timeSlice;
                    remainingBurstTime[j] -= timeSlice;
                } else {
                    time += remainingBurstTime[j];
                    waitingTime[j] = time - burstTime[j];
                    remainingBurstTime[j] = 0;
                }
            }
        }
        if (done) break;
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to calculate average times and display results
void calculateAverageTimes(int n, int burstTime[], int timeSlice) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Calculate waiting and turnaround times
    calculateWaitingTime(n, burstTime, timeSlice, waitingTime);
    calculateTurnaroundTime(n, burstTime, waitingTime, turnaroundTime);

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnaroundTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Calculate and display averages
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n, timeSlice;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n];

    // Input burst times
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Input time slice (quantum)
    printf("Enter the time slice (quantum): ");
    scanf("%d", &timeSlice);

    // Calculate and display average times
    calculateAverageTimes(n, burstTime, timeSlice);

    return 0;
}
