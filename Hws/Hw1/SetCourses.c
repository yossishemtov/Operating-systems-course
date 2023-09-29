#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void writeToCourses(char *courseCode, char *courseName, char *courseDay, char *startTime, char *endTime);

int main(int argc, char *argv[])
{
    char *courseCode, *courseName, *courseDay, *startTime, *endTime;

    courseCode = argv[0];
    courseName = argv[1];
    courseDay = argv[2];
    startTime = argv[3];
    endTime = argv[4];

    writeToCourses(courseCode, courseName, courseDay, startTime, endTime);
}

void writeToCourses(char *courseCode, char *courseName, char *courseDay, char *startTime, char *endTime)
{
    int writefd;
    char whatInFile[1024];
    ssize_t n;
    char courseInformation[256];
    int rbytes;
    char firstline[256] = "ID Name Day Start End\n";

    writefd = open("Courses/Courses.txt", O_RDWR | O_CREAT, 0664);
    lseek(writefd, 0, SEEK_SET);
    if ((rbytes = read(writefd, whatInFile, 1024)) <= 0)
        write(writefd, firstline, strlen(firstline));
    lseek(writefd, 0, SEEK_END);
    if (strlen(whatInFile) != 0)
    {
        // If no courses exist in the courses file, add a \n before the course information
        strcpy(courseInformation, "");
        strcat(courseInformation, courseCode);
        strcat(courseInformation, " ");
        strcat(courseInformation, courseName);
        strcat(courseInformation, " ");
        strcat(courseInformation, courseDay);
        strcat(courseInformation, " ");
        strcat(courseInformation, startTime);
        strcat(courseInformation, " ");
        strcat(courseInformation, endTime);

        write(writefd, &courseInformation, strlen(courseInformation));
    }
    write(writefd, "\n", 1);
    close(writefd);
    printf("Wrote course information:  %s  to Courses.txt file\n", courseInformation);

    exit(1);
}
