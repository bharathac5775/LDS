#include <stdio.h>

void calculateWaitingTime(int n, int burstTime[], int priority[], int waitingTime[]) {
    waitingTime[0] = 0;  // First process has no waiting time

    for (int i = 1; i < n; i++) {
        waitingTime[i] = 0;
        for (int j = 0; j < i; j++) {
            waitingTime[i] += burstTime[j];
        }
    }
}

void calculateTurnaroundTime(int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverageTimes(int n, int burstTime[], int priority[]) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Sorting the processes based on priority (ascending order of priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (priority[i] > priority[j]) {
                // Swap burst time
                int tempBurst = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = tempBurst;
                
                // Swap priority
                int tempPriority = priority[i];
                priority[i] = priority[j];
                priority[j] = tempPriority;
            }
        }
    }

    // Calculate waiting and turnaround times
    calculateWaitingTime(n, burstTime, priority, waitingTime);
    calculateTurnaroundTime(n, burstTime, waitingTime, turnaroundTime);

    // Display results
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], priority[i], waitingTime[i], turnaroundTime[i]);
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
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n], priority[n];

    // Input burst times and priorities
    printf("Enter the burst time and priority for each process (lower number indicates higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &burstTime[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    // Calculate and display average times
    calculateAverageTimes(n, burstTime, priority);

    return 0;
}
