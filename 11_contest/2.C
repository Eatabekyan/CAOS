#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int CreatPidAndWork(int* stts, int* cnt, char* str){
  int status = *stts;
  int count = *cnt;
  pid_t pid = fork();
  if (pid == 0) {
      if (scanf("%s", str) == EOF) {
          exit(0);
      }
      exit(1);
  } else {
      waitpid(pid, &status, 0);
      count = count + WEXITSTATUS(status);
  }
  *cnt = count;
  *stts = status;
}

int main()
{ 
    char str[4096];
    int count = 0;
    int status;
    do {
      CreatPidAndWork(&status, &count, str);
    } while (status);
    printf("%d", count);
    return 0;
}
