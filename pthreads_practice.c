#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// global variables
int amountOfMail = 0;
pthread_mutex_t mutex;

// prototypes - function declarations
void *routine(); // a simple pointer function for createThreads example
void *incrementMail(void *id); // pointer function for the mutex/race condition example

void example1_createThreads(); // example on how to create threads 
void example2_raceConditions(); // using mutex's to prevent race conditions example

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL); // initialize the mutex to a default value

    //example1_createThreads();
    example2_raceConditions();

    pthread_mutex_destroy(&mutex); // destroy/free the memory of the allocated mutex

    return 0;
}

// our basic routine function
void *routine() {
    printf("We created a thread...\n");
    sleep(3); // simulating some work being done by this routine for 3 seconds
    printf("Exiting thread...\n");
}

void *incrementMail(void *id) {
    int i, tid = *(int*)id;
    for (i = 0; i < 10; i++) {
        //printf("Locking thread %d...\n", tid);
        pthread_mutex_lock(&mutex);
        amountOfMail++;
        pthread_mutex_unlock(&mutex);
        //printf("Unlocking thread %d...\n", tid);
    }
}

void example1_createThreads() {
    pthread_t tempThreads[3];
    int thread_id = 0;
    
    // created a thread of the function "routine", create does have a return value
    // we can also put these statements in a if condition and still initiate/create a thread along with getting their ID
    if (thread_id = pthread_create(&tempThreads[0], NULL, &routine, NULL))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);
    
    if (thread_id = pthread_create(&tempThreads[1], NULL, &routine, NULL))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);

    if (thread_id = pthread_create(&tempThreads[2], NULL, &routine, NULL))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);

    // so the threads above are all running concurrently / parallel (not the same but not sure which one it is)

    // equivalent to saying "wait" for a process to end but for threads, so the parent will wait for the thread to finish execution
    // can also use a for loop 
    pthread_join(tempThreads[0], NULL);
    pthread_join(tempThreads[1], NULL);
    pthread_join(tempThreads[2], NULL);
}

void example2_raceConditions() {
    pthread_t tempThreads[2];
    int thread_id = 0;
    int id1 = 1, id2 = 2;
    
    if (thread_id = pthread_create(&tempThreads[0], NULL, &incrementMail, &id1))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);
    
    if (thread_id = pthread_create(&tempThreads[1], NULL, &incrementMail, &id2))
        fprintf(stderr, "ERROR! Thread %d encountered an issue...\n", thread_id);

    pthread_join(tempThreads[0], NULL);
    pthread_join(tempThreads[1], NULL);

    printf("The current amount of mail is: %d\n", amountOfMail);
}