#include <sys/types.h>
#include <sys/syscall.h>

long syscall(long number, ...);
int main() { syscall(SYS_write, 1, "Hello, World!\n", 14); }
void _start() { syscall(SYS_exit, main()); }