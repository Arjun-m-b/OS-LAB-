#include <stdio.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    int swapped;

    for(i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }
}

int main()
{
    int n, ct[20], tat[20], current_time = 0;
    int wt[20], sumwt = 0, sumtat = 0;

    printf("Enter the number of processes:");
    scanf("%d", &n);

    int at[20], bt[20], pid[20];

    printf("Enter the AT and BT\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
        scanf("%d", &bt[i]);
        pid[i] = i + 1;
    }

    bubbleSort(at, n);

    for(int i = 0; i < n; i++)
    {
        if(current_time < at[i])
            current_time = at[i];

        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        current_time = ct[i];

        sumwt += wt[i];
        sumtat += tat[i];
    }

    int awt = sumwt / n;
    int atat = sumtat / n;

    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], wt[i], tat[i]);
    }

    printf("AWT = %d\n", awt);
    printf("ATAT = %d\n", atat);

    return 0;
}