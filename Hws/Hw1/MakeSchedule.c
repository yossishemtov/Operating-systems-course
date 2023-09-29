#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void checkIfSchedule(char *studentId);
int checkIfCourseExist(char *courseId);
char *showCourses();
char *extractcourse(int index);
void writeToSchedule(char *courseInformation, char *studentId);
void checkIfEmpty(char *studentId);

int main(int argc, char *argv[])
{
    char userCourse[256], userChoice[256];
    char *courseInformation;
    int courseCheckStatus = 0;
    checkIfSchedule(argv[0]);

    while (strcmp(userCourse, "Exit") != 0 && strcmp(userChoice, "Exit") != 0)
    {
        // Asking the user for the courseid
        printf("Please insert course id:\n");
        fgets(userCourse, 256, stdin);
        userCourse[strlen(userCourse) - 1] = '\0';

        // CHecking if the course exists, if it does, searching the entire course information from Courses.txt
        if (strcmp(userCourse, "Exit") == 0)
        {
            checkIfEmpty(argv[0]);
        }

        courseCheckStatus = checkIfCourseExist(userCourse);
        if (courseCheckStatus == 0)
        {
            printf("Course does not Exist!\n");
        }
        else
        {
            courseInformation = extractcourse(courseCheckStatus);
            printf("Confirm? (Type Confirm)\n");
            fgets(userChoice, 256, stdin);
            userChoice[strlen(userChoice) - 1] = '\0';

            // If user types Confirm, write the courseinformation to his schedule.txt file, else deleting it.
            if (strcmp(userChoice, "Confirm") == 0)
            {

                strcat(courseInformation, "\n");
                writeToSchedule(courseInformation, argv[0]);
                printf("Wrote course to Schedule.txt of userid: %s\n", argv[0]);
            }
            else
            {
                printf("Didn't wrote to schedule because not confirmed\n");
                if (strcmp(userChoice, "Exit") == 0)
                    checkIfEmpty(argv[0]);
            }
        }
    }
}

// Checking if schedule.txt exists, if not it creates it
void checkIfSchedule(char *studentId)
{
    int readfd, rbytes;
    char buff[1024];
    ssize_t n;
    char path[256] = "student/";
    char firstline[256] = "ID Name Day Start End\n";
    strcat(path, studentId);
    strcat(path, "/Schedule.txt");

    readfd = open(path, O_WRONLY | O_CREAT, 0664);

    if (readfd == -1)
        printf("Error while creating schedule file for user");

    lseek(readfd, 0, SEEK_SET);
    if ((rbytes = read(readfd, buff, 1024)) <= 0)
        write(readfd, firstline, strlen(firstline));
    close(readfd);
}

// Check if CourseId exists in Courses.txt and returns the modulo of column it is at
int checkIfCourseExist(char *courseId)
{
    int i, j = 0, count = 0;
    char *coursesInFile;
    char lastCourse[1][256], word[256];
    int index = 0;

    coursesInFile = showCourses();
    for (i = 0; i < strlen(coursesInFile); i++)
    {

        if (coursesInFile[i] != ' ' && coursesInFile[i] != '\0' && coursesInFile[i] != '\n')
        {
            word[j++] = coursesInFile[i];
        }
        else
        {
            word[j] = '\0';
            if (count % 5 == 0)
            {
                if (strcmp(courseId, word) == 0)
                    return count;
            }
            count++;
            strcpy(lastCourse[0], word);
            j = 0;
        }
    }

    free(coursesInFile);
    return 0;
}

// Returning all the courses from Courses.txt file
char *showCourses()
{
    int readfd;
    char *buff = malloc(sizeof(char) * 1024);
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
        return buff;
    }
}

// Getting the course information from the Courses.txt file
char *extractcourse(int index)
{
    int i, j = 0, count = 0;
    char *coursesInFile;
    char *word = malloc(sizeof(char) * 256);

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

            if (count == index / 5)
            {
                printf("%s\n", word);
                return word;
            }
            count++;
            j = 0;
        }
    }
    return NULL;
    free(coursesInFile);
}

// Writing to the userId Schedule.txt file the courseinformation provided
void writeToSchedule(char *courseInformation, char *studentId)
{
    int writefd;
    char buff[1024];
    ssize_t n;
    char path[256] = "student/";
    strcat(path, studentId);
    strcat(path, "/Schedule.txt");
    strcpy(buff, courseInformation);

    writefd = open(path, O_RDWR | O_APPEND);

    if (writefd == -1)
        printf("Error while reading Schedule.txt of user to write");

    printf("%s", courseInformation);
    write(writefd, &buff, strlen(courseInformation));
    close(writefd);
}

void checkIfEmpty(char *studentId)
{
    int readfd;
    char buff[1024];
    ssize_t n;
    char firstline[256] = "ID Name Day Start End\n";

    char path[256] = "student/";
    strcat(path, studentId);
    strcat(path, "/Schedule.txt");

    readfd = open(path, O_RDONLY);

    if (readfd == -1)
        printf("Error while reading Schedule.txt of user to write");

    read(readfd, buff, 256);

    if (strlen(buff) <= strlen(firstline))
        remove(path);
}
