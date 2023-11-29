#include <stdio.h>

int main() {
    int n, qt, i, count = 0, temp, sq = 0;
    float atat = 0, awt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n], rem_bt[n];

    printf("Enter the burst time of the process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d = ", i);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter the quantum time: ");
    scanf("%d", &qt);

    while (1) {
        for (i = 0, count = 0; i < n; i++) {
            temp = qt;
            if (rem_bt[i] == 0) {
                count++;
                continue;
            }
            if (rem_bt[i] > qt) {
                rem_bt[i] = rem_bt[i] - qt;
            } else if (rem_bt[i] <= qt) {
                temp = rem_bt[i];
                rem_bt[i] = 0;
            }
            sq = sq + temp;
            tat[i] = sq;
        }
        if (n == count)
            break;
    }

    printf("\nProcess Burst Time Turnaround Time Waiting Time\n");
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        printf("\n%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], tat[i], wt[i]);
    }

    awt = awt / n;
    atat = atat / n;

    printf("\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", atat);

    return 0;
}