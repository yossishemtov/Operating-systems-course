#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 256

//int compString(char[] stringOne, char[] stringTwo);
void checkFile(int code);

int main(int argc, char* argv[]) {
	//Opening file veriables
	int fileOne, fileTwo;
	//Num of bytes returned from read
	int rBytesFileOne, rBytesFileTwo;
	//Buffer for charecters
	char buffFileOne[BUFSIZE], buffFileTwo[BUFSIZE];

	if(argc!=3){
		printf("Usage ./Ex1Lab3 file1 file2");
		return 1;
	}

	//Opening the two files
	fileOne = open(argv[1], O_RDONLY);
	checkFile(fileOne);

	fileTwo = open(argv[2], O_RDONLY);
	checkFile(fileTwo);

	while((rBytesFileOne = read(fileOne, &buffFileOne, BUFSIZE)) > 0 && (rBytesFileTwo = read(fileTwo, &buffFileTwo, BUFSIZE)) > 0){
		if(strcmp(buffFileOne, buffFileTwo) !=0){
			printf("Different files\n");
			return 0;
		}
	}

	if((rBytesFileTwo && rBytesFileOne) != 0){
		printf("Different files\n");
		return 0;		
	}

	printf("Identical files\n");
	return 1;



}

//Checking for errors in handler return code
void checkFile(code){
	if(code == -1){
		perror("Error happend in openning one of the files");
		exit(3);
	}
}

//Checking if two string are identical
// int compString(char[] stringOne, char[] stringTwo){
// 	int i = 0;

// 	for(int i; i<256; i++){
// 		if(stringOne[i] != stringTwo[i])
// 			return 0;
// 	}

// 	return 1;
// }