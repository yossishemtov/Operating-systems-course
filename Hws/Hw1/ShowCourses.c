#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void showCourses();

int main(int argc, char *argv[])
{
    showCourses();
    exit(1);
}

void showCourses()
{
    int readfd;
    char buff[1024];
    ssize_t n;

    readfd = open("Courses/Courses.txt", O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
        printf("Error while reading Courses.txt");

    n = read(readfd, buff, 1024);
    buff[n] = '\0';

    // Checks for errors while reading to the buffer
    if (n < 0)
    {
        printf("Error while reading from file descriptor");
    }
    else
    {
        buff[n] = '\0'; // End of the buffer
        printf("%s", buff);
    }
}