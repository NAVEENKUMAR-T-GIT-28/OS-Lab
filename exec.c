#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child (PID %d) running ls -l:\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec failed");
        exit(1);
    } else {
        int status;
        wait(&status);
        printf("Parent: child exited with %d\n", WEXITSTATUS(status));
    }
    return 0;
}