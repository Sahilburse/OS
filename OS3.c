#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int burst_time;   // Burst time
    int arrival_time; // Arrival time
};

// Function to implement Shortest Job First (Preemptive) scheduling algorithm
void SJF(struct Process processes[], int n) {
    int remaining_time[n];
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
  
    // Copy the burst times to the remaining_time array
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;

    while (completed < n) {
        int shortest_job = -1;
        int shortest_job_burst = INT_MAX;
        
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] < shortest_job_burst && remaining_time[i] > 0) {
                shortest_job = i;
                shortest_job_burst = remaining_time[i];
            }
        }
        
        // If no process is found, increment the current time
        if (shortest_job == -1) {
            current_time++;
            continue;
        }
        
        // Reduce the remaining burst time of the selected process by 1
        remaining_time[shortest_job]--;

        // If the process is completed
        if (remaining_time[shortest_job] == 0) {
            completed++;
            
            // Calculate waiting time and turnaround time
            int waiting_time = current_time - processes[shortest_job].arrival_time - processes[shortest_job].burst_time + 1;
            int turnaround_time = current_time - processes[shortest_job].arrival_time + 1;
            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;

            printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n", processes[shortest_job].pid, waiting_time, turnaround_time);
        }

        current_time++;
    }

    // Calculate average waiting time and turnaround time
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

// Function to implement Round Robin scheduling algorithm
void roundRobin(struct Process processes[], int n, int quantum) {
    int remaining_time[n];
    int completed = 0, current_time = 0;
    int waiting_time[n], turnaround_time[n];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Copy the burst times to the remaining_time array
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                // If remaining burst time is greater than the quantum, execute for the quantum
                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } 
                // If remaining burst time is less than or equal to the quantum, execute for the remaining burst time
                else {
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - processes[i].burst_time - processes[i].arrival_time;
                    turnaround_time[i] = current_time - processes[i].arrival_time;
                    remaining_time[i] = 0;
                    completed++;

                    // Calculate waiting time and turnaround time
                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];

                    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n", processes[i].pid, waiting_time[i], turnaround_time[i]);
                }
            }
        }float
    }

    // Calculate average waiting time and turnaround time
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    printf("\nEnter the time quantum for Round Robin: ");
    scanf("%d", &quantum);
    
    printf("\nShortest Job First (Preemptive):\n");
    SJF(processes, n);
    
    printf("\nRound Robin:\n");
    roundRobin(processes, n, quantum);

    return 0;
}

