#define _CRT_SECURE_NO_WARNINGS


int main(int argc, char* argv[]){

    char string[1] = "c";
  int pipe1[2], pipe2[2];
  int pid;
  pipe(pipe1);
  pipe(pipe2);
  write(pipe1[1], string, sizeof(char));  // (*)
  pid = fork();



}


int countNumWords(char* buff){
    int numOfWords = 0;
    int i = 0;

    while(buff[i] != '\0'){
        
    }
}

int countNumLines(char* buff){
    //Calculate the number of lines in the buffer
    int i = 0;
    int count = 0;

    while(buff[i] != '\0'){
        if(buff[i] == "\n")
            count++;;
    
    i++;
    }

}

int countChars(char* buffer){
    //Calculate the number of chars in the buffer
    int i = 0;
    int count = 0;

    while(buffer[i]!='\0'){
        count++;
    i++;
    }

    return count;
}