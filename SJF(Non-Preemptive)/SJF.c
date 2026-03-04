#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20];
    int completed[20] = {0};
    int i, count = 0;
    int current_time = 0, min_index;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // SJF Non-Preemptive Scheduling
    while (count < n) {
        min_index = -1;

        // Find process with smallest burst time among arrived processes
        for (i = 0; i < n; i++) {
            if (at[i] <= current_time && completed[i] == 0) {
                if (min_index == -1 || bt[i] < bt[min_index]) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            ct[min_index] = current_time + bt[min_index];
            tat[min_index] = ct[min_index] - at[min_index];
            wt[min_index] = tat[min_index] - bt[min_index];

            current_time = ct[min_index];
            completed[min_index] = 1;
            count++;
        } else {
            current_time++;  // CPU Idle
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output Table
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}