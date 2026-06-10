#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid;
    int tickets;
};

int main() {
    int n, i, totalTickets = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter tickets for Process %d: ", p[i].pid);
        scanf("%d", &p[i].tickets);

        totalTickets += p[i].tickets;
    }

    srand(time(NULL));

    printf("\nLottery Scheduling Order:\n");

    for(i = 0; i < 10; i++) {  // Simulate 10 CPU allocations
        int winner = rand() % totalTickets + 1;
        int sum = 0, j;

        for(j = 0; j < n; j++) {
            sum += p[j].tickets;

            if(winner <= sum) {
                printf("CPU Allocation %d -> Process P%d\n",
                       i + 1, p[j].pid);
                break;
            }
        }
    }

    return 0;
}
