#include <stdio.h>
#define MAX 10

int main() {
    int n, tq;
    int at[MAX], bt[MAX], rt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int queue[MAX], front = 0, rear = 0;
    int time = 0, count = 0;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    queue[rear++] = 0;

    while (count < n) {
        int idx = queue[front++];
        if (front == MAX) front = 0;
        if (rt[idx] > 0) {
            if (rt[idx] > tq) {
                time += tq;
                rt[idx] -= tq;
            } else {
                time += rt[idx];
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                avgWT += wt[idx];
                avgTAT += tat[idx];
                rt[idx] = 0;
                count++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i != idx && at[i] <= time && rt[i] > 0) {
                int alreadyInQueue = 0;
                for (int j = front; j != rear; j = (j+1)%MAX) {
                    if (queue[j] == i) {
                        alreadyInQueue = 1;
                        break;
                    }
                }
                if (!alreadyInQueue) {
                    queue[rear++] = i;
                    if (rear == MAX) rear = 0;
                }
            }
        }

        if (rt[idx] > 0) {
            queue[rear++] = idx;
            if (rear == MAX) rear = 0;
        }

        if (front == rear && count < n) {
            int nextArrival = 9999, nextIdx = -1;
            for (int i = 0; i < n; i++) {
                if (rt[i] > 0 && at[i] < nextArrival) {
                    nextArrival = at[i];
                    nextIdx = i;
                }
            }
            time = at[nextIdx];
            queue[rear++] = nextIdx;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT/n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT/n);

    return 0;
}
