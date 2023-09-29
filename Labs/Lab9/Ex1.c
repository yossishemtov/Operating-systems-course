#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#define K 5
#define N 10

int stk[N];  // Stack array
int idx = 0; // Index of the top element in the stack
sem_t seml, semnf, semne; // Semaphores for coordinating access to the stack

void* tFunc(void* p);
void stkPush(int num);
int stkPop();

void stkPush(int num)
{
    sem_wait(&semnf); // Wait for available space in the stack
    sem_wait(&seml); // Wait for exclusive access to the stack
    stk[idx++] = num; // Push the number onto the stack
    sem_post(&seml); // Release access to the stack
    sem_post(&semne); // Signal that there is an element in the stack
}

int stkPop()
{
    int num;
    sem_wait(&semne); // Wait for an element to be present in the stack
    sem_wait(&seml); // Wait for exclusive access to the stack
    num=stk[--idx]; // Pop and return the top element from the stack
    sem_post(&seml); // Release access to the stack
    sem_post(&semnf); // Signal that there is an available space in the stack
    return num;
}

int main(int argc, char* argv[])
{
    sem_init(&seml, 0, 1); // Initialize the semaphore for stack access (1 = available)
    sem_init(&semnf, 0, N); // Initialize the semaphore for available spaces in the stack (N = maximum capacity)
    sem_init(&semne, 0, 0); // Initialize the semaphore for elements in the stack (0 = no elements)

    pthread_t tArr[K]; // Array of thread IDs
    int i = 0, ans[K]; // Variables for loop iteration and thread creation result

    // Create K threads
    for (i = 0; i < K; i++)
    {
        ans[i] = pthread_create(&tArr[i], NULL, tFunc, NULL);
        if (ans[i] != 0)
        {
            printf("Error in thread creation\n");
            exit(1);
        }
    }

    sleep(10); // Sleep for 10 seconds to allow the threads to execute

    return 0;
}

void* tFunc(void* p)
{
    int num;
    while (1)
    {
        num = rand() % 100; // Generate a random number

        // Randomly choose to push or pop from the stack
        if (rand() % 2)
        {
            stkPush(num); // Push the random number onto the stack
            printf("Push %d\n", num);
        }
        else
        {
            printf("Pop %d\n", stkPop()); // Pop an element from the stack and print it
        }

        sleep(1); // Sleep for 1 second before the next operation
    }
}

