#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {       
        printf("Child process with PID %d\n", getpid());
        execlp("/bin/ls","ls",NULL);
    }
    else
    {
        wait (NULL);
        printf("Child Complete");
    }
}