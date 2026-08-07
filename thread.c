#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>


void* thread_function(void* arg) {
    printf("Thread: Thread ID: %lu, Process ID: %d\n", pthread_self(), getpid());
    return NULL;
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
    
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: Process ID: %d, Parent ID: %d\n", getpid(), getppid());
        
        pthread_t thread;
        if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread in child process");
            return 1;
        }

        pthread_join(thread, NULL);

        printf("Child Process: Thread finished, Process ID: %d\n", getpid());

    } else {
        printf("Parent Process: Process ID: %d, Child Process ID: %d\n", getpid(), pid);

        pthread_t thread;
        if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread in parent process");
            return 1;
        }
        pthread_join(thread, NULL);

        printf("Parent Process: Thread finished, Process ID: %d\n", getpid());
        wait(NULL);
        printf("Parent Process: Child process finished, Process ID: %d\n", getpid());
    }

    return 0;
}