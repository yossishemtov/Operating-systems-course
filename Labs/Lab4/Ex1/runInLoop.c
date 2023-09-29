#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

int main(int argc, char* argv[]){
    int i = 0, status;
    int id;

    if(argc!=3)
    printf("The number of arguments is not equal 2");


    for(i=0; i < atoi(argv[2]); i++){
        id=fork();
        if(id==0){
            execl(argv[1], NULL);
            perror("Error in execl");
        }
    }

    for(i=0; i<atoi(argv[2]);i++ )
        wait(&status);
    printf("END\n");




}