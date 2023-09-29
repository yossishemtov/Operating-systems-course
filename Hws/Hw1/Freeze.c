#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void changeAttempts(char *userId);
void changingDirPermissions(char *userId);

int main(int argc, char *argv[])
{
    char *userId = argv[0];
    changeAttempts(userId);
    // changingDirPermissions(userId);
    printf("Student %s is now on freeze!\n", userId);

    return 1;
}

// Changing the attempts number for a user to 3, which will lock options to him
// While logged in, user will have restrictions in modifing courses etc..
void changeAttempts(char *userId)
{
    char path[256];
    char buffer[256];
    int fd;

    strcpy(path, "student/");
    strcat(path, userId);
    strcat(path, "/attempts.txt");

    fd = open(path, O_WRONLY, 0777);

    if (fd == -1)
        printf("Something happend while writing attempts.txt");

    strcpy(buffer, "3");

    write(fd, &buffer, strlen(buffer));

    close(fd);
}

// void changingDirPermissions(char* userId){
//     char path[256];
//     char buffer[256];
//     int fd;

//     strcpy(path, "student/");
//     strcat(path, userId);

//     //chmod(path, 660);
// }