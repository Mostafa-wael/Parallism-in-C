#include <omp.h>
#include <stdio.h>
#define n 10
// gcc  -fopenmp q2b1.c 
int f(int a)
{
    printf("%d ", a);
    return a;
}
int main()
{
    int A[n + 1] = {0};
    omp_set_num_threads(8);
#pragma omp parallel for 
    for (int i = 0; i <= n; i++)
    {
#pragma omp critical // no need for it 
        {
            A[i] += f(i);
        }
    }

    for (int i = 0; i <= n; i++)
    {
        printf("\nA[%d] = %d ", i, A[i]);
    }
}