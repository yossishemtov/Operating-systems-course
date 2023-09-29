#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t semA, semB;

void* create_message ( void* str ){
    int i = 0;
    for ( i = 0; i < 10; i++ )  
    {
        sem_wait(&semB);
        printf ( "I've wrote a message #%d. %s\n", i+1, (char*) str );
        sem_post(&semA);
        
    }
}


int main (){

//Initiating semA and SemB
    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 1);

    pthread_t  thread; 
    int i = 0;

    if(pthread_create (&thread, NULL, create_message, (void*)"Thread A")!=0){
        printf("Error in thread creation\n");
        exit(1);
    }



    //SemA will start with 0, which means this loop will be entered after
    //SemA will be with 1, which will only happen in create_message func
    for ( i = 0; i < 10; i++ ) {
        sem_wait(&semA);
        printf ( "The message #%d was printed. Thread B \n", i+1 );
        printf("\n");
        sem_post(&semB);
    }
        
    pthread_join(thread, NULL);
}