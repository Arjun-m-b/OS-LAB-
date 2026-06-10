#include <stdio.h>
#include <stdlib.h>

int state[5];
int fork_[5];

#define THINKING 0
#define HUNGRY 1
#define EATING 2

void test(int ph)
{
    if(state[ph] == HUNGRY &&
       state[(ph + 4) % 5] != EATING &&
       state[(ph + 1) % 5] != EATING)
    {
        state[ph] = EATING;
        printf("Philosopher %d takes forks %d and %d\n",
               ph + 1,
               (ph + 4) % 5 + 1,
               ph + 1);
    }
}

void take_fork(int ph)
{
    state[ph] = HUNGRY;

    printf("Philosopher %d is Hungry\n", ph + 1);

    test(ph);
}

void put_fork(int ph)
{
    state[ph] = THINKING;

    printf("Philosopher %d putting forks %d and %d down\n",
           ph + 1,
           (ph + 4) % 5 + 1,
           ph + 1);

    printf("Philosopher %d is Thinking\n",
           ph + 1);

    test((ph + 4) % 5);
    test((ph + 1) % 5);
}

int main()
{
    int ch, ph;

    for(int i = 0; i < 5; i++)
        state[i] = THINKING;

    while(1)
    {
        printf("\n1.Take Fork");
        printf("\n2.Put Fork");
        printf("\n3.Exit");

        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                printf("Enter philosopher no:");
                scanf("%d", &ph);
                take_fork(ph - 1);
                break;

            case 2:
                printf("Enter philosopher no:");
                scanf("%d", &ph);
                put_fork(ph - 1);
                break;

            case 3:
                exit(0);
        }
    }

    return 0;
}