#include <stdio.h>
#include <unistd.h>

#define N 10


//Calculating fibonacci sequence of order 10
int main(){
    int c1, c2, t, i;
    c2=1, c1=0;
    
    for(i=1; i<N; i++){
        switch(fork()){
            case -1:
            printf("Error creating process\n");
            return -1;

            case 0:
            //Taking the previous number, saving it in t
            //Calculating the next number in c2
                t = c2;
                c2 = t + c1;
                c1 = t;
                break;

            default:
                i=N;
            break;
        }

    }
    wait(NULL);
    printf(" %d", c2);
}