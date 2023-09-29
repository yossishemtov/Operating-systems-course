#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void checkCommand(char *userCommand);

int main(int argc, char *argv[])
{

    char userInput[256];

    // Infinite loop until userInput is LogOut, checking the user command through checkCommand function
    while (strcmp(userInput, "LogOut") != 0)
    {

        printf("LecShell>");
        fgets(userInput, 256, stdin);
        userInput[strlen(userInput) - 1] = '\0';

        checkCommand(userInput);
    }

    return 1;
}

void checkCommand(char *userCommand)
{
    pid_t pid;
    int i, j = 0, count = 0, status;
    int numberOfActualArguments = 0;
    char arguments[6][256];
    char word[256];

    // Extracting the user command with its arguments to array namd arguments, and putting each in an index
    for (i = 0; i < strlen(userCommand) + 1; i++)
    {
        if (userCommand[i] != ' ' && userCommand[i] != '\0' && userCommand[i] != '\n')
        {
            word[j++] = userCommand[i];
        }
        else
        {
            word[j] = '\0';
            numberOfActualArguments++;
            strcpy(arguments[count++], word);
            j = 0;
        }
    }

    // Decide what is the command to execute and how to handle it
    if (strcmp(arguments[0], "SetCourses") == 0)
    {
        if (numberOfActualArguments == 6)
        {
            pid = fork();
            if (pid == 0)
                execl("SetCourses", arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "GetSchedule") == 0)
    {
        if (numberOfActualArguments == 2)
        {
            pid = fork();
            if (pid == 0)
                execl("GetSchedule", arguments[1], (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "DeleteStudent") == 0)
    {
        if (numberOfActualArguments == 2)
        {
            pid = fork();
            if (pid == 0)
                execl("DeleteStudent", arguments[1], (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "Freeze") == 0)
    {
        if (numberOfActualArguments == 2)
        {
            pid = fork();
            if (pid == 0)
                execl("Freeze", arguments[1], (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "Approve") == 0)
    {
        if (numberOfActualArguments == 2)
        {
            pid = fork();
            if (pid == 0)
                execl("Approve", arguments[1], (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "ShowCourses") == 0)
    {
        if (numberOfActualArguments == 1)
        {
            pid = fork();
            if (pid == 0)
                execl("ShowCourses", (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Not enough or too many arguments provided to SetCourse instruction\n");
        }
    }
    else if (strcmp(arguments[0], "LogOut") == 0)
    {
        exit(1);
    }
    else
        printf("Not Supported\n");
}
