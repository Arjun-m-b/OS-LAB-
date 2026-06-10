#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
    char type[10];
} Process;

typedef struct
{
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q)
{
    q->front = q->rear = -1;
}

int isEmpty(Queue *q)
{
    return (q->front == -1);
}

void enqueue(Queue *q, int v)
{
    if(q->rear == MAX - 1)
        return;

    if(q->front == -1)
        q->front = 0;

    q->items[++q->rear] = v;
}

int dequeue(Queue *q)
{
    if(isEmpty(q))
        return -1;

    int val = q->items[q->front];

    if(q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;

    return val;
}

void sortByArrival(Process p[], int n)
{
    Process temp;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(p[j].arrival > p[j + 1].arrival)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void mlq()
{
    int n;

    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Type(system/user): ");
        scanf("%s", p[i].type);

        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
    }

    sortByArrival(p, n);

    Queue systemQ, userQ;

    initQueue(&systemQ);
    initQueue(&userQ);

    int time = 0;
    int completed = 0;
    int i = 0;

    int current = -1;

    int gantt[MAX];
    int gtime[MAX];

    int gindex = 0;

    while(completed < n)
    {
        while(i < n && p[i].arrival <= time)
        {
            if(strcmp(p[i].type, "system") == 0)
                enqueue(&systemQ, i);
            else
                enqueue(&userQ, i);

            i++;
        }

        if(current == -1)
        {
            if(!isEmpty(&systemQ))
                current = dequeue(&systemQ);
            else if(!isEmpty(&userQ))
                current = dequeue(&userQ);
            else
            {
                time++;
                continue;
            }
        }

        gantt[gindex] = p[current].pid;
        gtime[gindex] = time;
        gindex++;

        p[current].remaining--;
        time++;

        if(p[current].remaining == 0)
        {
            p[current].completion = time;
            completed++;
            current = -1;
        }
    }

    gtime[gindex] = time;

    float twt = 0;
    float ttat = 0;

    for(int i = 0; i < n; i++)
    {
        p[i].turnaround =
            p[i].completion - p[i].arrival;

        p[i].waiting =
            p[i].turnaround - p[i].burst;

        twt += p[i].waiting;
        ttat += p[i].turnaround;
    }

    printf("\nGantt Chart:\n");

    for(int i = 0; i < gindex; i++)
        printf("P%d ", gantt[i]);

    printf("\n");

    for(int i = 0; i <= gindex; i++)
        printf("%d ", gtime[i]);

    printf("\n");

    printf("\nPID\tTYPE\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].type,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    printf("AWT = %.2f\n", twt / n);
    printf("ATAT = %.2f\n", ttat / n);
}

int main()
{
    mlq();
    return 0;
}