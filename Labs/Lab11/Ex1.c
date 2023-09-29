#include <stdio.h>
int main() {
  char string[1] = "c";
  int pipe1[2], pipe2[2];
  int pid;
  pipe(pipe1);
  pipe(pipe2);
  write(pipe1[1], string, sizeof(char));  // (*)
  pid = fork();
 
 
  if (pid == 0) 
 	 while (1) {
			read(pipe1[0], string, sizeof(char));
			printf("a\n");
			write(pipe2[1], string, sizeof(char));		
	}	
  else if (pid > 0)

while(1){
        read(pipe2[0], string, sizeof(char));
		printf("b\n");
		write(pipe1[1], string, sizeof(char));     
	}
	
    return 0;
}


//The second process is reading from pipe1, the first process is writing to pipe1
//The second process is writing to pipe2, the first process is reading from pipe2

//b.

//c. Wouldnt run since every pipe is waiting for a write,
//But non is being written to so no one will run