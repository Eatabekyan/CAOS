#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void PrintPid() {
 int status;
 pid_t pid0 = getpid();
 printf("my pid = %ld\n", (long) pid0);
 pid_t parent_pid = getppid();
 printf("parent pid = %ld\n", (long) parent_pid);
 waitpid(pid0, &status, 0); 
}

int main() {
 int status;
 PrintPid();
 pid_t pid = fork();
 if(pid == 0) {
    PrintPid();  
    _exit(0);
     
 }
 waitpid(pid, &status, 0);
 printf("GOODBYE");
}