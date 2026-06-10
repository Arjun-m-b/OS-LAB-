#include <stdio.h>

typedef struct
{
    int id;
    int period;
    int execution;
    int remaining;
    int deadline;
} Task;

int main()
{
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[n];

    for(int i = 0; i < n; i++)
    {
        printf("Task %d\n", i + 1);

        printf("Period: ");
        scanf("%d", &t[i].period);

        printf("Execution Time: ");
        scanf("%d", &t[i].execution);

        t[i].id = i + 1;
        t[i].remaining = 0;
        t[i].deadline = t[i].period;
    }

    int hyper = 1;

    for(int i = 0; i < n; i++)
        hyper *= t[i].period;

    printf("\nSchedule:\n");

    for(int time = 0; time < hyper; time++)
    {
        for(int i = 0; i < n; i++)
        {
            if(time % t[i].period == 0)
            {
                t[i].remaining = t[i].execution;
                t[i].deadline = time + t[i].period;
            }
        }

        int selected = -1;

        for(int i = 0; i < n; i++)
        {
            if(t[i].remaining > 0)
            {
                if(selected == -1 ||
                   t[i].period < t[selected].period)
                {
                    selected = i;
                }
            }
        }

        if(selected != -1)
        {
            printf("%d -> T%d\n",
                   time,
                   t[selected].id);

            t[selected].remaining--;
        }
        else
        {
            printf("%d -> Idle\n", time);
        }
    }

    return 0;
}