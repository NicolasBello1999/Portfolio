#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// prototypes - function declarations
void *routine();

int main(int argc, char const *argv[])
{
    pthread_t tempThreads[3];
    int thread_id = 0;
    
    // created a thread of the function "routine", create does have a return value
    if (thread_id = pthread_create(&tempThreads[0], NULL, &routine, NULL))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);
    
    pthread_create(&tempThreads[1], NULL, &routine, NULL);
    pthread_create(&tempThreads[2], NULL, &routine, NULL);

    // so the threads above are all running concurrently or in parallel

    // equivalent to saying "wait" for a process to end but for threads, so the parent will wait for the thread to finish execution
    pthread_join(tempThreads[0], NULL);
    pthread_join(tempThreads[1], NULL);
    pthread_join(tempThreads[2], NULL);

    return 0;
}

// our basic routine function
void *routine() {
    printf("We created a thread...\n");
    sleep(3); // simulating some work being done by this routine for 3 seconds
    printf("Exiting thread...\n");
}