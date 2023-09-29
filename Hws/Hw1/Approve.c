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
    printf("Student %s is now on Approved!\n", userId);
}

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

    strcpy(buffer, "0");

    write(fd, &buffer, strlen(buffer));

    close(fd);
}