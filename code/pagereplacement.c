#include <stdio.h>

void fifo(int pages[], int n, int f)
{
    int frames[20];
    int index = 0, faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }

    printf("FIFO Page Faults = %d\n", faults);
}

void lru(int pages[], int n, int f)
{
    int frames[20], time[20];
    int faults = 0;

    for(int i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = -1;
    }

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            for(int j = 0; j < f; j++)
            {
                if(frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                pos = 0;

                for(int j = 1; j < f; j++)
                {
                    if(time[j] < time[pos])
                        pos = j;
                }
            }

            frames[pos] = pages[i];
            time[pos] = i;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

void optimal(int pages[], int n, int f)
{
    int frames[20];
    int faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            for(int j = 0; j < f; j++)
            {
                if(frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                int farthest = -1;

                for(int j = 0; j < f; j++)
                {
                    int k;

                    for(k = i + 1; k < n; k++)
                    {
                        if(frames[j] == pages[k])
                            break;
                    }

                    if(k == n)
                    {
                        pos = j;
                        break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            faults++;
        }
    }

    printf("Optimal Page Faults = %d\n", faults);
}

int main()
{
    int n, f, ch;
    int pages[50];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);


    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}
