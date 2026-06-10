#include <stdio.h>

void roundrobin(
    int n,
    int *at,
    int *bt,
    int *rt,
    int *ct,
    int tq)
{
    int time = 0, comp = 0;

    int vis[n];

    for(int i = 0; i < n; i++)
        vis[i] = 0;

    while(comp < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                found = 1;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    comp++;
                }
            }
        }

        if(found == 0)
            time++;
    }
}
int main()
{
    int n, tq;

    printf("Enter number of processes:");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n], ct[n];

    printf("Enter quantum time:");
    scanf("%d", &tq);

    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("Process %d\n", pid[i]);

        scanf("%d", &at[i]);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    roundrobin(n, at, bt, rt, ct, tq);

    printf("PID\tAT\tBT\tCT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i]);
    }

    return 0;
}