#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], priority[n], ct[n], completed[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT and Priority of process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
        completed[i] = 0;
    }

    int time = 0, count = 0;
    while (count < n) {
        int index = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i] && priority[i] < highestPriority) {
                highestPriority = priority[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            time += bt[index];
            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            completed[index] = 1;
            count++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}
