#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 20
#define M 30

int myMatrix[N][M];
int flag = 0;

void* searchInArray(void* userNumber);
void* searchInArrayForThreadOne(void* userNumber);
void* searchInArrayForThreadTwo(void* userNumber);


int main(int atgc, char* argv[]){
    int i = 0, j = 0;
    int userNumber;
    pthread_t firstThread, secondThread;

    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            myMatrix[i][j] = rand() % 100;
        }
    }

    printf("Please enter a numebr between 1-100: \n");
    scanf("%d", &userNumber);
    
//Two threads, one for even and one for odd number of row
    pthread_create(&firstThread, NULL, searchInArrayForThreadOne, (void*)&userNumber);
    pthread_create(&secondThread, NULL, searchInArrayForThreadTwo, (void*)&userNumber);

    pthread_join(firstThread, NULL);
    pthread_join(secondThread, NULL);

    if(flag == 1)
        printf("The user number has been found in the array\n");
    else
        printf("The user number has not been found in the array");
}

//Threads function to search in the array
//Each seartching in diffrent rows (odd or even)
void* searchInArrayForThreadOne(void* userNumber){
    int i = 0, j = 0;

    for(i=0; i<N; i++){
        if(i%2 == 0){
            for(j=0; j<M; j++){
                if(myMatrix[i][j] == *(int*)userNumber){
                    flag=1;
                    return (void*) 1;
                }
            }
        }
        if(flag == 1){
            return (void *)1;
        }

}

    return (void *)0;
}

void* searchInArrayForThreadTwo(void* userNumber){
    int i = 0, j = 0;

    for(i=0; i<N; i++){
        if(i%2 == 1){
            for(j=0; j<M; j++){
                if(myMatrix[i][j] == *(int*)userNumber){
                    flag=1;
                    return (void*) 1;
                }
            }
        }
        if(flag == 1){
            return (void *)1;
        }
    }

    return (void *)0;

}