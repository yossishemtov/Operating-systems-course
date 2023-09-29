#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void showSchedule(char *userId);
void errorMsg(char *msg);

int main(int argc, char *argv[])
{

    showSchedule(argv[0]);
    exit(1);
}

void showSchedule(char *userId)
{
    int readfd;
    char buff[1024];
    ssize_t n;
    char path[256] = "student/";

    strcat(path, userId);
    readfd = open(path, O_RDONLY);
    if (readfd == -1)
    {
        printf("Student not Found.");
        exit(1);
    }
    close(readfd);
    strcat(path, "/Schedule.txt");

    readfd = open(path, O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
    {
        printf("Student not register!");
        exit(1);
    }

    n = read(readfd, buff, 1024);
    buff[n] = '\0';

    // Checks for errors while reading to the buffer
    if (n < 0)
    {
        printf("Student not register!\n");
        // errorMsg("Error while reading from file descriptor");
        exit(1);
    }
    else
    {
        buff[n] = '\0'; // End of the buffer
        close(readfd);
        printf("%s\n", buff);
    }
}

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}
