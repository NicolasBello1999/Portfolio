#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int arrivalTime, burstTime, completionTime,
    waitingTime, turnAroundTime, remainingTime, id;
} process;

void roundRobin(process **pcb, int quanta, int size);

int main(int argc, char const *argv[])
{
    // create a new process control block (PCB) and initialize its attributes
    process *pcb = malloc(sizeof(process) * 10);


    return 0;
}

void roundRobin(process **pcb, int quanta, int size) {
    int i = 0, j, amountCompleted = 0;

    while (amountCompleted != size) {
        
    }
}

process *bubbleSortByArrival(process *process, int size) {
    int i, j;
    process *temp = NULL;

    for (i = 0; i < size - 1; i++) {
        for (j = 1; j < size - 1 - i; j++) {
            if (process[i].arrivalTime > process[j].arrivalTime) {
                temp = &process[i];
                process[i] = process[j];
                process[j] = (*temp);
            }
        }
    }
}
