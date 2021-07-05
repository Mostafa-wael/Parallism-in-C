#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// gcc -lpthread  code2.c
#define NUM_THREADS 4
#define n 10
int allTsDistribution;
int remanningDistribution;
int A[n] = {0};
pthread_mutex_t lock;
//**********************
int g(int a, int b)
{
    return 1;
}
void *doLoop(void *thread_id)
{
    long tid = (long)thread_id;
    int i = (tid - 1) * n / NUM_THREADS;
    int boundary = i + allTsDistribution + (remanningDistribution * (tid == (NUM_THREADS))); // if it is the last Thread, add the "remanningDistribution" to it
    boundary = thread_id == NUM_THREADS ? n : boundary;                                      // last element in the array (i < n)
    printf("\nthread #%ld!, start = %d, boundary = %d \n", tid, i, boundary);
    for (i; i < boundary; i++)
    {
        for (int j = 0; j < n; j++)
        {

            pthread_mutex_lock(&lock);
            A[i] += g(j, i);
            pthread_mutex_unlock(&lock);
        }
        printf("thraed %d A[i] = %d\n ", tid, A[i]);
    }

    // pthread_exit(NULL);
}
int main()
{
    allTsDistribution = n / NUM_THREADS;     // each Thread will have "allTsDistribution" numbers
    remanningDistribution = n % NUM_THREADS; // Last Thread will have "allTsDistribution" + "remanningDistribution" numbers
    pthread_mutex_init(&lock, NULL);
    pthread_t threads[NUM_THREADS];
    void *status;
    for (int t = 1; t <= NUM_THREADS; t++)
    {

        int rc = pthread_create(&threads[t], NULL, doLoop, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (int t = 1; t <= NUM_THREADS; t++)
        pthread_join(threads[t], &status);

    for (int i = 0; i < n; i++)
        printf("\nA[%d] = %d ", i, A[i]);

    return 0;
}
