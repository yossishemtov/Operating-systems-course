#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void deleteStudentDir(char *studentId);

int main(int argc, char *argv[])
{
    char *studentId = argv[0];

    printf("%s\n", studentId);
    deleteStudentDir(studentId);
}

void deleteStudentDir(char *studentId)
{
    char path[256];

    strcpy(path, "student/");
    strcat(path, studentId);
    strcat(path, "/attempts.txt");

    int code = remove(path);

    strcpy(path, "student/");
    strcat(path, studentId);
    strcat(path, "/Schedule.txt");

    code = remove(path);

    strcpy(path, "student/");
    strcat(path, studentId);

    code = remove(path);

    if (code)
        perror(studentId);
    else
        printf("Directory of %s, has been deleted successfuly\n", studentId);

    exit(1);
}