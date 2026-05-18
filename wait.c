#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child (PID %d) running...\n", getpid());
        sleep(2);
        printf("Child done.\n");
        exit(0);
    } else {
        int status;
        printf("Parent waiting for child %d...\n", pid);
        wait(&status);
        printf("Child exited with status: %d\n", WEXITSTATUS(status));
    }
    return 0;
}