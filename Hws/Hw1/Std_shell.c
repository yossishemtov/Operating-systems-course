#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void checkCommand(char *command, int accessMode, char *userId);

int main(int argc, char *argv[])
{
    int isBlocked = atoi(argv[0]);
    char *userName = argv[1];
    char *userId = argv[2];

    char userInput[256];

    while (strcmp(userInput, "LogOut") != 0)
    {

        printf("StdShell>");
        fgets(userInput, 256, stdin);
        userInput[strlen(userInput) - 1] = '\0';

        checkCommand(userInput, isBlocked, userId);
    }

    return 1;
}

void checkCommand(char *command, int accessMode, char *userId)
{

    pid_t pid;
    int status;

    // Check for the commands and returning a code to the main function accordingly
    if (strcmp(command, "ShowCourses") == 0)
    {
        pid = fork();
        if (pid == 0)
            execl("ShowCourses", (char *)NULL);
        wait(&status);
    }
    else if (strcmp(command, "GetNewCourse") == 0)
    {
        pid = fork();
        if (pid == 0)
            execl("GetNewCourse", (char *)NULL);
        wait(&status);
    }
    else if (strcmp(command, "MakeSchedule") == 0)
    {
        if (accessMode == 0)
        {
            pid = fork();
            if (pid == 0)
                execl("MakeSchedule", userId, (char *)NULL);
            wait(&status);
        }
        else
        {
            printf("Blocked Account! Permission denied\n");
        }
    }
    else if (strcmp(command, "LogOut") == 0)
    {
        printf("Goodbye\n");
        exit(1);
    }
    else if (strcmp(command, "GetSchedule") == 0)
    {
        if (accessMode == 0)
        {
            pid = fork();
            if (pid == 0)
                execl("GetSchedule", userId, (char *)NULL);
            wait(&status);
        }
        else
            printf("Blocked Account! Permission denied\n");
    }
    else
    {
        printf("Not supported\n");
    }
}
