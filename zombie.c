#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        printf("Child Process Started\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        sleep(5);

        printf("\nAfter parent termination:\n");
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
    }

    else
    {
        // Parent process
        printf("Parent Process Started\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is terminating...\n");
        exit(0);
    }

    return 0;
}