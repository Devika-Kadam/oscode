#include <stdio.h>
#include <stdlib.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
};

// Function to perform First-Come-First-Serve (FCFS) scheduling
void FCFS(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    printf("\n\nFCFS Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].process_id, waiting_time[i], turnaround_time[i]);
    }
}

// Function to perform Round Robin scheduling
void RoundRobin(struct Process processes[], int n, int quantum) {
    int remaining_time[n];
    int waiting_time[n], turnaround_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int time = 0;
    int completed = 0;

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - processes[i].burst_time;
                    turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }

        if (done)
            break;
    }

    printf("\n\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].process_id, waiting_time[i], turnaround_time[i]);
    }
}

// Function to perform Shortest Job First (SJF) scheduling
void SJF(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (complete < n) {
        int shortest = -1;
        int min_burst = 9999;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] < min_burst && remaining_time[j] > 0) {
                shortest = j;
                min_burst = remaining_time[j];
            }
        }

        if (shortest == -1) {
            time++;
        } else {
            remaining_time[shortest] = 0;
            complete++;

            waiting_time[shortest] = time - processes[shortest].arrival_time;
            turnaround_time[shortest] = waiting_time[shortest] + processes[shortest].burst_time;

            total_waiting_time += waiting_time[shortest];
            total_turnaround_time += turnaround_time[shortest];

            time += processes[shortest].burst_time;
        }
    }

    printf("\n\nSJF Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t%.1f\n", processes[i].process_id, (float)waiting_time[i], (float)turnaround_time[i]);
    }
}

void PriorityNonPreemptive(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], response_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (complete < n) {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] > 0) {
                if (highest_priority == -1 || processes[j].priority < highest_priority) {
                    highest_priority = processes[j].priority;
                    highest_priority_idx = j;
                }
            }
        }

        int idx = highest_priority_idx;
        remaining_time[idx] = 0;
        complete++;

        response_time[idx] = time - processes[idx].arrival_time;
        waiting_time[idx] = time - processes[idx].arrival_time;
        turnaround_time[idx] = waiting_time[idx] + processes[idx].burst_time;

        total_waiting_time += waiting_time[idx];
        total_turnaround_time += turnaround_time[idx];

        time += processes[idx].burst_time;
    }

    float average_waiting_time = total_waiting_time / n;
    printf("\n\nNon-Preemptive Priority Scheduling:\n");
    printf("\nProcess\tWaiting Time\tTurn-around Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t\t%.1f\t\t\t%.1f\n", processes[i].process_id, (float)waiting_time[i], (float)turnaround_time[i], (float)response_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}

void PriorityPreemptive(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], response_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (complete < n) {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] > 0) {
                if (highest_priority == -1 || processes[j].priority < highest_priority) {
                    highest_priority = processes[j].priority;
                    highest_priority_idx = j;
                }
            }
        }

        int idx = highest_priority_idx;

        if (idx == -1) {
            time++;
        } else {
            remaining_time[idx]--;

            if (remaining_time[idx] == 0) {
                complete++;
                response_time[idx] = time - processes[idx].arrival_time + 1;
                turnaround_time[idx] = time - processes[idx].arrival_time + 1;
                waiting_time[idx] = turnaround_time[idx] - processes[idx].burst_time;
                total_waiting_time += waiting_time[idx];
                total_turnaround_time += turnaround_time[idx];
            }

            time++;
        }
    }

    float average_waiting_time = total_waiting_time / n;
    printf("\n\nPreemptive Priority Scheduling:\n");
    printf("Process\tWaiting Time\tTurn-around Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t\t%.1f\t\t\t%.1f\n", processes[i].process_id, (float)waiting_time[i], (float)turnaround_time[i], (float)response_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}



int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
     for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    int quantum;
    printf("\nEnter Quantum for Round Robin Scheduling: ");
    scanf("%d", &quantum);
    RoundRobin(processes, n, quantum);
    
    FCFS(processes, n);

    SJF(processes, n);

    PriorityNonPreemptive(processes, n);
    PriorityPreemptive(processes, n);


    return 0;
}

  

