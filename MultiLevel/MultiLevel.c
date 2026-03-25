#include <stdio.h>


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int PID[n], AT[n], BT[n], TYPE[n];
    int CT[n], TAT[n], WT[n], Start[n];

    int systemQueue[n], userQueue[n];
    int sysCount = 0, userCount = 0;

    int i, j, temp;
    int time = 0;

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter PID: ");
        scanf("%d", &PID[i]);
        printf("Enter Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Enter Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Enter Type (0 = System, 1 = User): ");
        scanf("%d", &TYPE[i]);
    }

    // Step 1: Separate into queues
    for(i = 0; i < n; i++) {
        if(TYPE[i] == 0) {
            systemQueue[sysCount++] = i;
        } else {
            userQueue[userCount++] = i;
        }
    }

    // Step 2: Sort System Queue by Arrival Time (FCFS)
    for(i = 0; i < sysCount - 1; i++) {
        for(j = 0; j < sysCount - i - 1; j++) {
            if(AT[systemQueue[j]] > AT[systemQueue[j + 1]]) {
                temp = systemQueue[j];
                systemQueue[j] = systemQueue[j + 1];
                systemQueue[j + 1] = temp;
            }
        }
    }

    // Sort User Queue by Arrival Time (FCFS)
    for(i = 0; i < userCount - 1; i++) {
        for(j = 0; j < userCount - i - 1; j++) {
            if(AT[userQueue[j]] > AT[userQueue[j + 1]]) {
                temp = userQueue[j];
                userQueue[j] = userQueue[j + 1];
                userQueue[j + 1] = temp;
            }
        }
    }

    // Step 3: Execute System Processes
    for(i = 0; i < sysCount; i++) {
        int p = systemQueue[i];

        if(time < AT[p]) {
            time = AT[p];
        }

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    // Step 4: Execute User Processes
    for(i = 0; i < userCount; i++) {
        int p = userQueue[i];

        if(time < AT[p]) {
            time = AT[p];
        }

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    // Step 5: Display Results
    printf("\n\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], TYPE[i],
               CT[i], TAT[i], WT[i]);
    }

    return 0;
}
