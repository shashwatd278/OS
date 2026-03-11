#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], priority[n];
    for(int i = 0; i < n; i++){
        printf("Enter AT, BT and Priority for P%d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
        rt[i] = bt[i];
    }

    int time = 0, completed = 0;
    while(completed < n){
        int index = -1;
        int highestPriority = 9999;

        for(int i = 0; i < n; i++){
            if(at[i] <= time && rt[i] > 0){
                if(priority[i] < highestPriority){
                    highestPriority = priority[i];
                    index = i;
                }
            }
        }

        if(index == -1){
            time++;
        }
        else{
            rt[index]--;
            if(rt[index] == 0){
                ct[index] = time + 1;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
                completed++;
            }

            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}
