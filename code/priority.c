#include <stdio.h>

void nonpre(
    int n,
    int *pid,
    int *at,
    int *bt,
    int *priority,
    int *ct,
    int *tat,
    int *wt,
    int *completed)
{
    int time = 0, count = 0;

    while(count < n)
    {
        int idx = -1;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && completed[i] == 0)
            {
                if(idx == -1 || priority[i] < priority[idx])
                    idx = i;
            }
        }

        if(idx != -1)
        {
            time += bt[idx];

            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            completed[idx] = 1;
            count++;
        }
        else
        {
            time++;
        }
    }
}

void pre(
    int n,
    int *pid,
    int *at,
    int *bt,
    int *priority,
    int *ct,
    int *tat,
    int *wt,
    int *completed)
{
    int time = 0, count = 0;

    int rt[n];

    for(int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
        completed[i] = 0;
    }

    while(count < n)
    {
        int idx = -1;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && completed[i] == 0)
            {
                if(idx == -1 || priority[i] < priority[idx])
                    idx = i;
            }
        }

        if(idx == -1)
        {
            time++;
        }
        else
        {
            rt[idx]--;
            time++;

            if(rt[idx] == 0)
            {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                completed[idx] = 1;
                count++;
            }
        }
    }
}

int main()
{
    int n;

    printf("Enter number of processes:");
    scanf("%d", &n);

    int at[n], bt[n], pri[n];
    int pid[n], ct[n], tat[n], wt[n], comp[n];

    int ch;

    printf("1. Non Preemptive\n2. Preemptive\n");
    scanf("%d", &ch);

    for(int i = 0; i < n; i++)
    {
        printf("AT BT Priority for Process %d:\n", i + 1);

        scanf("%d%d%d",
              &at[i],
              &bt[i],
              &pri[i]);

        comp[i] = 0;
        pid[i] = i + 1;
    }

    switch(ch)
    {
        case 1:
            nonpre(n,pid,at,bt,pri,ct,tat,wt,comp);
            break;

        case 2:
            pre(n,pid,at,bt,pri,ct,tat,wt,comp);
            break;

        default:
            printf("Invalid");
            return 1;
    }

    float atat = 0, awt = 0;

    for(int i = 0; i < n; i++)
    {
        atat += tat[i];
        awt += wt[i];
    }

    atat /= n;
    awt /= n;

    printf("PID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               pri[i], ct[i],
               tat[i], wt[i]);
    }

    printf("ATAT=%f\n", atat);
    printf("AWT=%f\n", awt);

    return 0;
}