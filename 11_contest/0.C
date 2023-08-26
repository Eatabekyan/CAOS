#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int status, i = 0;
    pid_t pid;
    while (1) {
        pid = fork();
        if (pid > 0) {
            waitpid(pid, &status, 0);
            break;
        }
        if (pid == -1) {
            printf("%i\n", i + 1);
            break;
        }
        ++i;
    }
}