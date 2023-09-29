#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUMOFPKIDIM 4

void Calls(int City1, int City2);
void* Func(void* cityNum);

int eachPakid[NUMOFPKIDIM] = {0}; // array representing each pakid

//One mutex for generation of random call
//One mutex to prevent deadlocks while city1 calling city2
//Cities semaphores represent are for blocking each city that is already calling
//checkForRule semaphores are to prevent the rule that is on the exercise requirement which is
//While city num 2 and 3 are on call, 0 and 1 will wait, where as if 0 and 1 are on call first, 2 and 3 can call regularly

sem_t pakidCalls;
sem_t mutex;
sem_t cities[NUMOFPKIDIM];
sem_t checkForRule[NUMOFPKIDIM];

int main(int argc, char* argv[]){
    srand(time(NULL)); // Generate diffrent seed for each program run
    pthread_t pkidim[NUMOFPKIDIM]; 

    //Iitializing one mutex for generation of random number
    sem_init(&pakidCalls, 0, 1);
    sem_init(&mutex, 0, 1);



    int i=0;
    for(i=0; i<NUMOFPKIDIM; i++){
        //Initilalize new memory spot for an index sent to a thread
        eachPakid[i] = i;

        //There could be possibly max calls of two at each moment
        //Initialize cities semaphores for each city
        sem_init(&cities[i], 0, 1);
        sem_init(&checkForRule[i], 0, 1);

    }





    
    for(i=0; i<NUMOFPKIDIM; i++){
        //Using four threads to simulate calls
        if(pthread_create(&pkidim[i], NULL, Func, (void*)&eachPakid[i]) !=0){
            printf("Error in thread 1 creation\n");
            exit(1);
        }

    }

    sleep(20);

    for (i = 0; i < NUMOFPKIDIM; i++)
    {
        pthread_join(pkidim[i], NULL);
    }

    


}


void* Func(void* cityNum){
    
    //Casting the cityNum - the city that is calling
    //randomnumber is the city that is being called
    int cityNumCasted = *(int*)cityNum;
    int randomnumber = cityNumCasted;
    

    while(1){

        sem_wait(&pakidCalls);
        //Generate new number while the city calls for the same city as itself
        randomnumber = rand() % NUMOFPKIDIM;
        sem_post(&pakidCalls);

        if(cityNumCasted != randomnumber){
            //Making a call
            Calls(cityNumCasted, randomnumber);
        }

    }

}


void Calls(int City1, int City2){
    //City 0 is Karmiel, 1 Tiberias, 2 Haifa, 3 Tzfat

    //Checks if city is 2 or 3 or 3 or 2, decreasing checkForRule sumaphore accordinglt
    if((City1 == 2 || City1 == 3) && (City2 == 2 || City2 == 3)) {
        sem_wait(&checkForRule[0]);
        sem_wait(&checkForRule[1]);
    }


    //Using a mutex to between the sem_waits to prevent a deadlock
    //When a thread tries to take the second city that is being called
    sem_wait(&mutex);

    sem_wait(&cities[City1]);
    sem_wait(&cities[City2]);

    sem_post(&mutex);

    printf("%d started to talk with %d\n", City1, City2); 
    sleep(1); 
    printf("%d finished to talk with %d\n", City1, City2);

    if((City1 == 2 || City1 == 3) && (City2 == 2 || City2 == 3)) {
        sem_post(&checkForRule[1]);
        sem_post(&checkForRule[0]);
    }


    sem_post(&cities[City2]);
    sem_post(&cities[City1]);


}


