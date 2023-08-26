#include <sys/types.h>
#include <sys/syscall.h>

long syscall(long number, ...);
int main() { 
  char s;
  ssize_t ret = syscall(SYS_read,0,&s,sizeof(s));
  while(ret > 0){
    syscall(SYS_write,1,&s,ret);
    ret = syscall(SYS_read,0,&s,sizeof(s));
  }
}
void _start() { syscall(SYS_exit, main()); }