#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256

char* encrypt(char* bufferToEnc, char* replaceWith, int numOfChars, int cursorJmp);
void checkFile(int code);


int main(int argc, char* argv[]){
	int fromFile, fd_to, toFile, rBytesFileOne, wBytesFileTwo;
	char buffFrom[BUFSIZE];
	char* encrypted;

	if(argc!=4){
		printf("Usage ./createEncryptedCopy filename N STR");
		return 1;
	}

	int cursorJmp = atoi(argv[2]);


	mkdir("encrypted", 0777);

	fromFile = open(argv[1], O_RDONLY);
	checkFile(fromFile);

	fd_to = open("encrypted/a.txt", O_WRONLY|O_CREAT, 0666);
	checkFile(fd_to);


	while(rBytesFileOne = (read(fromFile, &buffFrom, BUFSIZE)>0)){
		encrypted = encrypt(buffFrom, argv[3], BUFSIZE, cursorJmp);
		printf(encrypted);

		wBytesFileTwo = write(fd_to, &encrypted, BUFSIZE);
		checkFile(wBytesFileTwo);
	}


	//closing files
	close(fromFile);
	close(fd_to);
	return 1;
}

//Checking for errors in handler return code
void checkFile(int code){
	if(code == -1){
		perror("Error happend in reading or writing one of the files");
		exit(3);
	}
}

char* encrypt(char* bufferToEnc, char* replaceWith, int numOfChars, int cursorJmp){
	int i = 0, j = 0, flag = cursorJmp, firstIndex=0;;
	int replaceWithLen = strlen(replaceWith);

	//Allocating new string for "encryption"
	char* newString = (char*) malloc(sizeof(char) * (cursorJmp*replaceWithLen + strlen(bufferToEnc)));



//Using the buffer to know how many charecters to add
	while(bufferToEnc[firstIndex] != '\0'){

		if(flag == 0){
		for(j = 0; j<replaceWithLen; j++){
			newString[i] = replaceWith[j];
			i++;
		}

		flag = cursorJmp;
	}
	newString[i] = bufferToEnc[firstIndex];
	i++;
	firstIndex++;
	flag--;
		
	}

	return newString;

}
