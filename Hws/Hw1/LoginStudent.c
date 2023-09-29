#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int openFileAndLogin(char *userName, char *password);
int tryLogin(char *word, char *userName, char *password);
void checkattempts();
void errorMsg(char *msg);
int increaseAttempts(char *id, int addAttempts);

char userNameGlobal[200], userIdGlobal[200];

int main(int argc, char *argv[])
{
    int status;

    if (argc != 2)
    {
        printf("You didn't provide username and password\n");
        exit(1);
    }
    status = openFileAndLogin(argv[0], argv[1]);

    if (status == 0)
    {
        // Permission 0 means there is no restrictions on the student account
        execl("Std_shell", "0", userNameGlobal, userIdGlobal, NULL);
    }
    else if (status == 2)
    {
        // Permission 2 means the account is on restriction and is locked, limited access to features will be given
        execl("Std_shell", "2", userNameGlobal, userIdGlobal, NULL);
    }
    else
    {
        exit(1);
    }
}

int openFileAndLogin(char *userName, char *password)
{
    int readfd;
    char buff[1024];
    ssize_t n;

    readfd = open("std_pass.txt", O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
        errorMsg("Error while reading std_Pass.txt");

    n = read(readfd, buff, 1024);
    buff[n] = '\0';

    // Checks for errors while reading to the buffer
    if (n < 0)
    {
        errorMsg("Error while reading from file descriptor\n");
    }
    else
    {
        buff[n] = '\0'; // End of the buffer
        close(readfd);
        return tryLogin(buff, userName, password);
    }
}

int tryLogin(char *wordbuff, char *userName, char *password)
{
    int i, j = 0, count = 0, userNumber = 0;
    char word[100], fileUser[100], filePass[100], userid[100];

    for (i = 0; i < strlen(wordbuff); i++)
    {

        // Extracting username and password from the file
        if (wordbuff[i] != ' ' && wordbuff[i] != '\n')
        {
            word[j++] = wordbuff[i];
        }
        else
        {
            word[j] = '\0';

            // Username and password would be at modulo 0 and 1 according to the columns provided in the file
            if (count != 0 && count != 1 && count != 2)
            {
                if (count % 4 == 0)
                {
                    strcpy(fileUser, word);
                }

                if (count % 4 == 1)
                {
                    strcpy(filePass, word);
                    // Comparing with the userprovided username and password
                }
                if (count % 4 == 2)
                {
                    if (strcmp(fileUser, userName) == 0)
                    {
                        strcpy(userid, word);
                        strcpy(userNameGlobal, fileUser);
                        strcpy(userIdGlobal, userid);

                        if (strcmp(filePass, password) == 0)
                        {
                            if (increaseAttempts(userid, 0) < 3)
                            {
                                printf("login successful\n");
                                return 0;
                            }

                            if (increaseAttempts(userid, 0) > 2)
                            {
                                printf("ACCOUNT LOCKED");
                                return 2;
                            }
                        }
                        else
                        {
                            printf("Incorrect password\n");
                            // Increasing number of attempts and checking if greater than 2
                            if (increaseAttempts(userid, 1) > 2)
                            {
                                printf("User %s is LOCKED! contact lecturer for release\n", userid);
                            }
                            return 1;
                        }
                    }

                    // Moving next in the userAttempts array
                    // userNumber++;
                }
            }
            count++;
            j = 0;
        }
    }

    // Return 1 if username and password not matching
    printf("Student Not Found!.\n");
    return 1;
}

// Increasing the number of attempts by addAttempts number of a specific user
int increaseAttempts(char *id, int addAttempts)
{
    int fd;
    int numberOfAttempts;
    char myPath[100] = "student/";
    char buffer[256];

    strcat(myPath, id);
    strcat(myPath, "/attempts.txt");

    fd = open(myPath, O_RDONLY, 0777);

    if (fd == -1)
        errorMsg("Something happend while reading attempts.txt");

    read(fd, buffer, 256);
    numberOfAttempts = atoi(buffer);
    numberOfAttempts += addAttempts;

    close(fd);

    fd = open(myPath, O_WRONLY, 0777);

    if (fd == -1)
        errorMsg("Something happend while reading for writing attempts.txt");

    sprintf(buffer, "%d", numberOfAttempts);

    write(fd, &buffer, strlen(buffer));

    close(fd);

    return numberOfAttempts;
}

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}
