#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// gcc -lpthread  code2.c
#define NUM_THREADS 4
#define n 10
int allTsDistribution;
int remanningDistribution;
int A[n + 1] = {0};
//**********************
int f(int a)
{
    printf("%d ", a);
    return a;
}
void *doLoop(void *thread_id)
{
    long tid = (long)thread_id;
    int i = (tid - 1) * n / NUM_THREADS;
    int boundary = i + allTsDistribution + (remanningDistribution * (tid == (NUM_THREADS))); // if it is the last Thread, add the "remanningDistribution" to it
    boundary = thread_id == NUM_THREADS ? n+1 : boundary; // last element in the array (i <= n)
    while (i < boundary)
    {
        A[i] += f(i);
        i++;
    }
   
    printf("\nthread #%ld!, start = %d, boundary = %d \n", tid, i, boundary);

    // pthread_exit(NULL);
}
int main()
{
    // calculate the distribution of students on the TAs
    allTsDistribution = n / NUM_THREADS;     // each Thread will have "allTsDistribution" numbers
    remanningDistribution = n % NUM_THREADS; // Last Thread will have "allTsDistribution" + "remanningDistribution" numbers
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

    for (int i = 0; i <= n; i++)
        printf("\nA[%d] = %d ", i, A[i]);

    return 0;
}
