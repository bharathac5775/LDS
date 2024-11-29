#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to store process details
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int priority;
} Process;

// Function to calculate average waiting time and turnaround time
void calculate_avg_times(Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

// Function to sort processes by arrival time (for FCFS, SJF, and Priority Scheduling)
void sort_by_arrival_time(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// FCFS Scheduling Algorithm
void fcfs(Process proc[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        current_time += proc[i].burst_time;
    }
    calculate_avg_times(proc, n);
}

// SJF Scheduling Algorithm (Non-Preemptive)
void sjf(Process proc[], int n) {
    int current_time = 0;
    sort_by_arrival_time(proc, n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].arrival_time <= current_time && proc[j].burst_time < proc[i].burst_time) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        current_time += proc[i].burst_time;
    }
    calculate_avg_times(proc, n);
}

// SJF with Preemption (SRTF)
void sjf_preemptive(Process proc[], int n) {
    int current_time = 0;
    int completed = 0;
    int min_burst_time_index;
    int remaining_processes = n;

    // Initialize remaining burst time
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Process scheduling loop
    while (remaining_processes > 0) {
        min_burst_time_index = -1;
        int min_burst_time = 9999999;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= current_time) {
                if (proc[i].remaining_time < min_burst_time) {
                    min_burst_time = proc[i].remaining_time;
                    min_burst_time_index = i;
                }
            }
        }

        // If no process is found (all processes have finished or no process arrived yet)
        if (min_burst_time_index == -1) {
            current_time++;
            continue;
        }

        // Execute the selected process for one unit of time
        proc[min_burst_time_index].remaining_time--;

        // If the process has completed execution
        if (proc[min_burst_time_index].remaining_time == 0) {
            proc[min_burst_time_index].completion_time = current_time + 1;
            proc[min_burst_time_index].turnaround_time = proc[min_burst_time_index].completion_time - proc[min_burst_time_index].arrival_time;
            proc[min_burst_time_index].waiting_time = proc[min_burst_time_index].turnaround_time - proc[min_burst_time_index].burst_time;
            remaining_processes--; // Process is completed
        }

        current_time++; // Increment time
    }

    // Calculate and display average waiting time and turnaround time
    calculate_avg_times(proc, n);
}


// Priority Scheduling Algorithm
void priority_scheduling(Process proc[], int n) {
    int current_time = 0;
    sort_by_arrival_time(proc, n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].arrival_time <= current_time && proc[j].priority < proc[i].priority) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        current_time += proc[i].burst_time;
    }
    calculate_avg_times(proc, n);
}

// Round Robin Scheduling Algorithm
void round_robin(Process proc[], int n, int time_slice) {
    int current_time = 0;
    int remaining_processes = n;
    int i = 0;

    while (remaining_processes > 0) {
        if (proc[i].remaining_time > 0) {
            if (proc[i].remaining_time > time_slice) {
                proc[i].remaining_time -= time_slice;
                current_time += time_slice;
            } else {
                current_time += proc[i].remaining_time;
                proc[i].remaining_time = 0;
                proc[i].completion_time = current_time;
                proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
                proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                remaining_processes--;
            }
        }
        i = (i + 1) % n;  // Move to the next process
    }
    calculate_avg_times(proc, n);
}

int main() {
    int n, time_slice;
    Process proc[MAX];

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, Priority (for Priority Scheduling), and Burst Time for Process %d: \n", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time;  // For SJF Preemptive and Round Robin
    }

    // Input time slice for Round Robin
    printf("Enter time slice for Round Robin: ");
    scanf("%d", &time_slice);

    // Run the scheduling algorithms
    printf("\n--- FCFS Scheduling ---\n");
    fcfs(proc, n);

    // Reset process data for next scheduling algorithm
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("\n--- SJF Scheduling ---\n");
    sjf(proc, n);

    // Reset process data for next scheduling algorithm
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("\n--- SJF Preemptive Scheduling ---\n");
    sjf_preemptive(proc, n);

    // Reset process data for next scheduling algorithm
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("\n--- Priority Scheduling ---\n");
    priority_scheduling(proc, n);

    // Reset process data for next scheduling algorithm
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("\n--- Round Robin Scheduling ---\n");
    round_robin(proc, n, time_slice);

    return 0;
}
