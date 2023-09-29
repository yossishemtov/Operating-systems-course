#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t semProduct;


//Machine A consuming if two products are available
void* machineAA(){

    while(1){
        sem_wait(&semProduct);
        sem_wait(&semProduct);

        printf("Collected AA\n");
    }
}


//Machine A producing product every two seconds
void* machineA(){

    while ( 1 ) {
        sleep(2);
        printf ( "Produced A\n");
        sem_post(&semProduct);
    }


}


int main (){
    sem_init(&semProduct, 0, 0);

    pthread_t  thread1, thread2; 


    
    //Each thread for each machine, one consuming and one producing
    if(pthread_create (&thread1, NULL, machineAA, NULL)!=0){
        printf("Error in thread 1 creation\n");
        exit(1);
    }

    if(pthread_create (&thread2, NULL, machineA, NULL)){
        printf("Error in thread 2 creation\n");
        exit(1);
    }



    //Main thread will exit after 20 seconds
    sleep(20);

}