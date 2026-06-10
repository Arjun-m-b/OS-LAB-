#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m];
    int max[n][m];
    int need[n][m];
    int avail[m];

    printf("Enter Allocation Matrix\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources\n");

    for(int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] =
                max[i][j] - alloc[i][j];
        }
    }

    int finish[n];
    int safe[n];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    safe[count++] = i;

                    for(int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("Unsafe State\n");
            return 0;
        }
    }

    printf("Safe Sequence:\n");

    for(int i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    return 0;
}