#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

char* dynamicInput();
char* userInput;

int main(int argc, char* argv){

    pid_t pid;
    int status;

    printf("$");
    userInput = dynamicInput();
    pid = fork();

  
        
    while(*userInput != 'q'){

    if(pid > 0){
    //for main process

        wait(&status);
        printf("$");
        userInput = dynamicInput();
        pid = fork();

    }else if (pid==0 && *userInput!='q'){
    //For the child processes

    //Checking if userImput last charecter is new line
        if (userInput[strlen(userInput) - 1] == '\n')
            userInput[strlen(userInput) - 1] = 0;

        execlp(userInput, (char *)NULL); 

        printf("ERROR\n");
        exit(1);

    }else{
        perror("Error forking\n");
        exit(1);
    }

    }
    if(pid>0)
        printf("END\n");
}

//Getting the input of the command from the user using dynamic allocation
//Couldv'e been done with a buffer with max 256 space (terminal max cmd buffer in a line)
char* dynamicInput(){
    char *str, myChar;
    int i=0;
    str = (char*)malloc(1*sizeof(char));

    while(myChar!='\n'){
        myChar = getc(stdin);
        str[i] = myChar;
        i++;
        realloc(str, i*sizeof(char));
    }
    str[i] = '\0';
    return str;
} 