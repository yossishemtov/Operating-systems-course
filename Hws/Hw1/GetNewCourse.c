#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char *showCourses();
void getNewCourse();
void errorMsg(char *msg);

int main(int argc, char *argv[])
{
    getNewCourse();
    exit(1);
}

char *showCourses()
{
    int readfd;
    char *buff = malloc(sizeof(char) * 1024);
    ssize_t n;

    readfd = open("Courses/Courses.txt", O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
        errorMsg("Error while reading Courses.txt");

    n = read(readfd, buff, 1024);
    buff[n] = '\0';

    // Checks for errors while reading to the buffer
    if (n < 0)
    {
        errorMsg("Error while reading from file descriptor");
    }
    else
    {
        buff[n] = '\0'; // End of the buffer
        return buff;
    }
}

// Extracting the last course by overwriting each course until the last course
// Print it at the end
void getNewCourse()
{
    int i, j = 0, count = 0;
    char *coursesInFile;
    char lastCourse[1][256], word[256];

    coursesInFile = showCourses();
    for (i = 0; i < strlen(coursesInFile); i++)
    {

        if (coursesInFile[i] != '\n')
        {
            word[j++] = coursesInFile[i];
        }
        else
        {
            word[j] = '\0';
            strcpy(lastCourse[0], word);
            j = 0;
        }
    }

    printf("%s\n", lastCourse[0]);

    // for (i = 0; i < 4; i++)
    // {
    //     printf("%s", lastCourse[i]);
    // }
}

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}
