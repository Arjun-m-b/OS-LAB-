#include <stdio.h>

int main()
{
    int n, i, j;

    int at[20], bt[20], tat[20], wt[20];
    int comp[20] = {0};

    int current_time = 0, completed_count = 0;
    int minbt, index;

    float avg_wt = 0;
    float avg_tat = 0;

    printf("Enter number of processes:");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter AT and BT for P%d:", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    while(completed_count < n)
    {
        minbt = 9999;
        index = -1;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= current_time && comp[i] == 0)
            {
                if(bt[i] < minbt)
                {
                    minbt = bt[i];
                    index = i;
                }
            }
        }

        if(index == -1)
        {
            current_time++;
        }
        else
        {
            int ct = current_time + bt[index];

            tat[index] = ct - at[index];
            wt[index] = tat[index] - bt[index];

            current_time = ct;

            comp[index] = 1;
            completed_count++;

            avg_wt += wt[index];
            avg_tat += tat[index];
        }
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("PID\tAT\tBT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               tat[i],
               wt[i]);
    }

    printf("AVG WT = %.2f\n", avg_wt);
    printf("AVG TAT = %.2f\n", avg_tat);

    return 0;
}