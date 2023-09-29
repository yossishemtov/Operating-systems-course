#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int checkCommand(char *command);
void makeDirectories();
void createAttemptsFile(char *path);
void errorMsg(char *msg);

int main(int argc, char *argv[])
{
    char userInput[256];
    int status;

    makeDirectories();

    while (strcmp(userInput, "exit") != 0)
    {

        printf("LockedShell>");
        fgets(userInput, 256, stdin);
        userInput[strlen(userInput) - 1] = '\0';
        checkCommand(userInput);
    }
}

// Checking if the command is valid and returning an integer accordingly
// If invalid command returned 0

int checkCommand(char *command)
{
    int i, j = 0, count = 0, status;
    char word[256];
    char wordsArr[3][256];
    pid_t pid;

    // Taking each command with its arguments and putting it in the char array wordsArr[3]

    for (i = 0; i < strlen(command) + 1; i++)
    {
        if (count < 3)
        {
            if (command[i] != ' ' && command[i] != '\0' && command[i] != '\n')
            {
                word[j++] = command[i];
            }
            else
            {
                word[j] = '\0';
                strcpy(wordsArr[count++], word);
                j = 0;
            }
        }
        else
        {
            printf("Not supported\n");
            return 0;
        }
    }

    // Check for the commands and returning a code to the main function accordingly
    if (count >= 1)
    {
        if (strcmp(wordsArr[0], "LoginStudent") == 0)
        {

            // Creating subprocess to execute student login
            pid = fork();
            if (pid == 0)
                execl("LoginStudent", wordsArr[1], wordsArr[2], (char *)NULL);
            wait(&status);
        }
        else if (strcmp(wordsArr[0], "LoginLecturer") == 0)
        {

            // Creating subprocess to execute lecturer login
            pid = fork();
            if (pid == 0)
                execl("LoginLecturer", wordsArr[1], wordsArr[2], (char *)NULL);
            wait(&status);
        }
        else if (count == 1 && strcmp(wordsArr[0], "exit") == 0)
        {
            printf("Goodbye...\n");
            exit(1);
        }
        else
        {
            printf("Not supported\n");
        }
    }

    return 0;
}

// Making directories according to the student id
void makeDirectories()
{
    int i, j = 0, count = 0, userNumber = 0;
    char word[100], fileUser[100], filePass[100], id[100], name[100], directory[100] = "student/";
    int readfd;
    char buff[1024];
    ssize_t n;

    mkdir("Courses", 0777);
    mkdir("student", 0777);

    readfd = open("std_pass.txt", O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
        errorMsg("Error while reading std_Pass.txt");

    n = read(readfd, buff, 1024);
    buff[n] = '\0';

    if (n < 0)
    {
        errorMsg("Error while reading from file descriptor");
    }

    for (i = 0; i < strlen(buff); i++)
    {

        // Extracting username and password from the file
        if (buff[i] != ' ' && buff[i] != '\n')
        {
            word[j++] = buff[i];
        }
        else
        {
            word[j] = '\0';

            // Not including the first four words because these are the columns names.
            //  Username, password, id and name would be equal to 0 1 2 and 3 at modulo 4 according to the columns provided in the file
            if (count != 0 && count != 1 && count != 2 && count != 4)
            {

                // Copying each property of a user to its appropriate fileUser,filePass, id and name fields.
                if (count % 4 == 0)
                {
                    strcpy(fileUser, word);
                }
                else if (count % 4 == 1)
                {
                    strcpy(filePass, word);
                }
                else if (count % 4 == 2)
                {
                    strcpy(id, word);
                    strcat(directory, word);
                    mkdir(directory, 0777);

                    // Also creating an attempts file for each student
                    createAttemptsFile(directory);
                    strcpy(directory, "student/");
                }
                else if (count % 4 == 3)
                {
                    strcpy(name, word);
                    userNumber++;
                }
            }
            count++;
            j = 0;
        }
    }

    close(readfd);
}

// Creating attempts.txt file with char of 0 at the beginning
void createAttemptsFile(char *path)
{
    int fd;
    char myPath[100];
    char zero[2] = "0";

    strcpy(myPath, path);
    strcat(myPath, "/attempts.txt");
    fd = open(myPath, O_WRONLY | O_CREAT, 0777);

    if (fd == -1)
        errorMsg("Something happend while creating attempts.txt");

    write(fd, &zero, 1);

    close(fd);
}

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}
