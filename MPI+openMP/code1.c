#include <mpi.h>
#include <stdio.h>
#define n 8
#define NUMPROC 4
int A[n] = {0};
int f(int x)
{
    return x;
}
int main(int argc, char *argv[])
{
    int numProc, rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int bufferSize = n / NUMPROC; // size of data to be sent or recieved
    if (rank == 0)                // if main process
    {
        //********************************
        // send array to other processes
        int startIndex, i;
        for (i = 1; i < NUMPROC; i++)
        {
            int startIndex = i * bufferSize;
            int sendBuffSize = (i == NUMPROC - 1) ? n - startIndex : bufferSize;
            if (i == NUMPROC - 1)
            {
                sendBuffSize = n - startIndex;
            }
            MPI_Send(&startIndex,
                     1, MPI_INT, i, 1,
                     MPI_COMM_WORLD);

            MPI_Send(&A[startIndex],
                     sendBuffSize,
                     MPI_INT, i, 2,
                     MPI_COMM_WORLD);
        }
//********************************
// calculating the values by the main process
#pragma omp parallel for
        for (int i = 0; i < bufferSize; i++)
#pragma omp critical // no need for it
            A[i] += f(i);
        //********************************
        // recieving the rest of the array from the rest of processes
        int recBufferSize;
        for (int i = 1; i < NUMPROC; i++)
        {
            MPI_Recv(&startIndex, 1, MPI_INT,
                     MPI_ANY_SOURCE, 1,
                     MPI_COMM_WORLD,
                     &status);

            recBufferSize = (startIndex / bufferSize == NUMPROC - 1) ? (n - startIndex) : bufferSize;
            MPI_Recv(&A[startIndex], recBufferSize, MPI_INT,
                     MPI_ANY_SOURCE, 2,
                     MPI_COMM_WORLD,
                     &status);
        }
        //********************************
        // test
        for (int i = 0; i < n; i++)
        {
            printf(" i= %d A[i] = %d\n ", i, A[i]);
        }
    }
    else // if another process
    {
        //********************************
        // recieve the start index from the main process
        int recBufferSize = (rank == NUMPROC - 1) ? n - (rank * bufferSize) : bufferSize;
        int startIndex = rank * bufferSize;
        for (int i = startIndex; i < startIndex + recBufferSize; i++)
        {
            A[i] += f(i);
        }

        //********************************
        // sending the array to the main process
        MPI_Send(&startIndex, 1, MPI_INT,
                 0, 1, MPI_COMM_WORLD);
        MPI_Send(&A[startIndex], recBufferSize, MPI_INT,
                 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}