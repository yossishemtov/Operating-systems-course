#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

unsigned long int counter = 0;

void* counterPlus();
void* printCounter();

int main(int argc, char* argv[]){
    pthread_t firstThread, secondThread;

    pthread_create(&firstThread, NULL, counterPlus, NULL);
    pthread_create(&secondThread, NULL, printCounter, NULL);


    pthread_join(firstThread, NULL);
    pthread_join(secondThread, NULL);
}

void* counterPlus(){
    while(1)
        counter++;
}

void* printCounter(){
    int i = 0;

    for(i=0; i<10; i++){
        printf("%li\n", counter);
        usleep(100000);
    }

    exit(1);
}