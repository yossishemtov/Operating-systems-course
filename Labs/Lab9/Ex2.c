#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 5
#define NUMBEROFVIEWERS 20
sem_t semMutex, semA, firstPerson;

int persons[N] = {0};
int countSpaces = N * 5;
int waiting = 0;

void *watchMovie(void *);
int wants(void *);
int endWatch(void *);

int main(int argc, char *argv[])
{
    // Initializing three semaphores, one for critical part
    // One for total spaces in the cinema
    // One to check for two or more people to watch movie

    sem_init(&semMutex, 0, 1);
    sem_init(&firstPerson, 0, 0);
    sem_init(&semA, 0, N * 5);

    pthread_t people[NUMBEROFVIEWERS];
    int i;
    int arr[NUMBEROFVIEWERS];

    for (int i = 0; i < NUMBEROFVIEWERS; i++)
    {
        arr[i] = i; // initialize array for diffrent memory location for threads

        if (pthread_create(&people[i], NULL, watchMovie, (void *)&arr[i]) != 0)
        {
            printf("Error in threads creations\n");
            exit(1);
        }
    }

    for (i = 0; i < NUMBEROFVIEWERS; i++)
    {
        pthread_join(people[i], NULL);
    }
}

int wants(void *p)
{

    sem_wait(&semMutex);
    sem_wait(&semA);
    printf("Person %d want to watch movie\n", *(int *)p);

    int i = 0;
    for (i = 0; i < N; i++)
    {
        // Checks if two persons or more wants  to watch a movie
        // For a cinema hall to open
        if (persons[i] > 0 && persons[i] < 5)
        {
            persons[i]++;
            printf("Person %d watch movie in room %d\n", *(int *)p, persons[i]);
            sem_post(&semMutex);
            return i + 1;
        }
    }

    if (waiting)
    {
        for (i = 0; i < N; i++)
        {
            // Checks if two persons or more wants  to watch a movie
            // For a cinema hall to open

            if (persons[i] == 0)
            {

                persons[i] = 2;
                printf("Person %d watch movie in room %d\n", waiting, persons[i]);
                printf("Person %d watch movie in room %d\n", *(int *)p, persons[i]);
                sem_post(&firstPerson);
                return i + 1;
                
            }


        }
        //sem_post(&semMutex);
    }else{
            waiting = *(int *)p;
            sem_post(&semMutex);
            sem_wait(&firstPerson);
            waiting=0;
            // sem_post(&semMutex);
        }
}

void *watchMovie(void *p)
{
    wants(p);
    endWatch(p);
}

int endWatch(void *p)
{
    printf("Person %d END watch movie\n", *(int *)p);
}