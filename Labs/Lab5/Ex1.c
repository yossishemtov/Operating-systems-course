#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20
#define M 30

int myMatrix[N][M] = {0};

void *initialRow(void *rowNum)
{

    int row = *(int *)rowNum;
    int i = 0;


    for (i = 0; i < M; i++)
    {
        myMatrix[row][i] = rand() % (100);
    }

    free(rowNum);
    pthread_exit(NULL);
}

void* sumRow(void *rowNum){

    int i = 0;
    int sum = 0;
    int* psum = (int*) malloc(sizeof(int*) * 1);

    for (i = 0; i < M; i++)
    {
        sum += myMatrix[*(int *)rowNum][i];
    }

    psum = &sum;
    return (void*)psum;
}

int main(int argc, char *argv[])
{
    int sum = 0;
    int* sumOfThread;
    int i = 0, j = 0;
    pthread_t myThreads[N];
    srand(time(NULL));

    
    for (i = 0; i < N; i++)
    {
        int* rowNum = (int*) malloc(sizeof(int));
        *rowNum = i;
        pthread_create(&myThreads[i], NULL, initialRow, (void *)rowNum);
    }

    for (i = 0; i < N; i++)
    {
        if (pthread_join(myThreads[i], NULL) != 0)
        {
            printf("Something went wrong with one of the threads");
            exit(1);
        }
    }

    //Printing the matrix
    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            printf("%d\t", myMatrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < N; i++)
    {
        pthread_create(&myThreads[i], NULL, sumRow, (void *)&i);
    }

    for (i = 0; i < N; i++)
    {
        if (pthread_join(myThreads[i], (void*)&sumOfThread) != 0)
        {
            printf("Something went wrong with one of the threads");
            exit(1);
        }else{
            sum+= *sumOfThread;
        }
    }
    printf("The sum of all rows is: %d\n", sum);
}