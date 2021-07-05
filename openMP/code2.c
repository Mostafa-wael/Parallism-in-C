#include <omp.h>
#include <stdio.h>
#define n 10
int g(int x,int y)
{
    return y;
}
int main(){
    int A[n] = {0};
    omp_set_num_threads(8);
    #pragma omp parallel for 
    for (int i = 0; i < n; i++) 
    {
        for(int j = 0; j < n; j++)
        { 
            #pragma omp critical 
             A[i] += g(j,i);
        } 
    }
    for (int i = 0; i <8; i++)
        {printf("A[i] = %d ", A[i]);}  
           
}