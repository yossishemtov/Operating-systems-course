#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 


void* threadfunc(void* numOfThread);


int currentThreadForCpu=0;


int main(int argc, char* argv[]){
    //Checking if one argument was provided
    if(argc!=2){
        printf("Not exact arguments provided");
    }

    int i = 0;
    int numOfThreads = atoi(argv[1]);

    pthread_t myThreads[numOfThreads];
    int myArr[numOfThreads];
    
    //Initiating threads and waiting for them
    for(i=0; i<numOfThreads; i++){
        myArr[i] = i;
        pthread_create(&myThreads[i],NULL, threadfunc, (void*)&myArr[i]);
    }

    for(i=0; i<numOfThreads; i++){
        pthread_join(myThreads[i], NULL);
    }
}

void* threadfunc(void* numOfThread){
    //A function for a thread, intended to calculate the time quanta
    struct timeval t1, t2;
    double elapsedTime;
    int threadNum = *(int *)numOfThread;


    //Infinite loop for a thread
    while(1){

    //Starting the time count and updating the current thread
    gettimeofday(&t1, NULL);
    currentThreadForCpu = threadNum;

    //If the thread has changed it will continue further to calculate the quanta time
        while(currentThreadForCpu == threadNum){
            gettimeofday(&t2, NULL);
        }

    
    //Printing the quanta time
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; 
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   
        printf("Time slice for thread %d  = %lf  ms.\n", currentThreadForCpu+1 ,elapsedTime) ;
        

    }
}
