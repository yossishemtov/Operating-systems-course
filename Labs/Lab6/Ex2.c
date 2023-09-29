#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 
#include <fcntl.h>     


#define N 15

void* threadAdds(void* counter);
void* printArr(void* thrdStruct);

typedef struct threadStruct{
    long int* countarr;
    int size;
}threadst;

int counttime = 0;

int main(int argc, char* argv[]){
    int userNumber;
    int i = 0;

    if(argc!=2){
        printf("Not exact arguments provided\n");
        exit(1);
    }

    userNumber = atoi(argv[1]);
    long int counter[userNumber];
    pthread_t myThreads[userNumber+1];

    threadst myTh;
    myTh.countarr = counter;
    myTh.size = userNumber;


    if(pthread_create(&myThreads[userNumber], NULL, (void*)printArr, (void*)&myTh) != 0){
        printf("Error in threads creations\n");
        exit(1);
    }

    for(i=0; i<userNumber; i++){
        counter[i] = 0;
        if(pthread_create(&myThreads[i],NULL, threadAdds, (void*)&counter[i])!=0){
            printf("Error in threads creations\n");
            exit(1);
        }
    }
    
    sleep(20);

    
    return 0;

}

void* threadAdds(void* counter){
    int i = 0;

    while(counttime <20){
        i++;
        *(int*)counter = i;
    }

}

void* printArr(void* thrdStruct){
    threadst* myStruct;
    myStruct = (threadst*)thrdStruct;
    long int* countarr = myStruct->countarr;
    int size = myStruct->size;
    int i=0;


    while(counttime<20){
    for(i=0; i<size; i++){
        printf("Thread %d counter: %ld\n", i+1, countarr[i]);
    }
    printf("\n");
    counttime +=2;
    sleep(2);
    }
}

