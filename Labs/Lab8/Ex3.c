#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t threadA, threadB, threadC;


//Using the semaphores inorder to print it exactly as the exercise requirement
void* printA(void * msg){
    while(1){
        sem_wait(&threadA);
        printf("A\n");
        sem_post(&threadB);

    }
}

void* printB(void * msg){
    while(1){
        sem_wait(&threadB);
        sem_wait(&threadB);
        printf("B\n");
        sem_post(&threadC);
    }
}

void* printC(void * msg){
    while(1){
        sem_wait(&threadC);
        printf("C\n");
        sem_post(&threadA);
        sem_post(&threadA);

    }
}

int main(){

    //Three semaphores are initialized, one for each print required
    sem_init(&threadA, 0, 2);
    sem_init(&threadB, 0, 0);
    sem_init(&threadC, 0, 0);

    pthread_t  thread1, thread2, thread3;

    //Three threads for each print
    if(pthread_create (&thread1, NULL, printA, NULL)!=0){
        printf("Error in thread A creation\n");
        exit(1);
    }

    if(pthread_create (&thread2, NULL, printB, NULL)){
        printf("Error in thread B creation\n");
        exit(1);        
    }

    if(pthread_create (&thread2, NULL, printC, NULL)){
        printf("Error in thread C creation\n");
        exit(1);        
    }


    sleep(5);

}