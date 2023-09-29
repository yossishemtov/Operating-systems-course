#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int openFileAndLogin(char *userName, char *password);
int tryLogin(char *word, char *userName, char *password);
void errorMsg(char *msg);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("You didn't provide username and password");
        exit(1);
    }

    if (openFileAndLogin(argv[0], argv[1]) == 0)
    {
        execl("Lec_shell", NULL);
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

    readfd = open("lec_pass.txt", O_RDONLY);

    // Checking error in the file descriptor handler
    if (readfd == -1)
        errorMsg("Error while reading std_Pass.txt");

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
        close(readfd);
        return tryLogin(buff, userName, password);
    }
}

int tryLogin(char *wordbuff, char *userName, char *password)
{
    int i, j = 0, count = 0, userNumber = 0;
    char word[100], fileUser[100], filePass[100];

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
            if (count != 0 && count != 1)
            {
                if (count % 4 == 0)
                {
                    strcpy(fileUser, word);
                }

                if (count % 4 == 1)
                {
                    strcpy(filePass, word);
                    // Comparing with the userprovided username and password
                    if (strcmp(fileUser, userName) == 0)
                    {

                        if (strcmp(filePass, password) == 0)
                        {
                            printf("login successful\n");
                            return 0;
                        }
                        else
                        {
                            printf("Incorrect password\n");
                            return 1;
                        }
                    }
                }
            }
            count++;
            j = 0;
        }
    }

    // Return 1 if username and password not matching
    printf("Username not exist.\n");
    return 1;
}

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}
