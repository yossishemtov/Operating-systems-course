#include <stdio.h>


int main() {
    int pid;
    pid = fork();


  if (pid == 0){

    while(1){
        printf("a\n");
    }

  }else if (pid > 0)

  while(1){
    printf("b\n");
	}

    
    return 0;


}