#include <stdio.h>

void waitingTime(int n, int bt[], int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void turnAroundTime(int n, int bt[], int wt[], int tat[]) {

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }
}

void avgTime(int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    waitingTime(n, bt, wt);
    turnAroundTime(n, bt, wt, tat);

    printf("Processes Burst time Waiting time Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];

        printf(" %d ", (i + 1));
        printf(" %d ", bt[i]);
        printf(" %d", wt[i]);
        printf(" %d\n", tat[i]);
    }

    float s = (float)total_wt / (float)n;
    int t = total_tat / n;

    printf("Average waiting time = %f", s);
    printf("\n");
    printf("Average turn around time = %d ", t);
}

void input(int *n, int bt[]) {
    printf("Enter the number of processes: ");
    scanf("%d", n);

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < *n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }
}

int main() {
    int n;
    int burst_time[100];

    input(&n, burst_time);
    avgTime(n, burst_time);

    return 0;
}