#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


void printcont(int fsize,char* contents, char* sub_str);
void wrkin(int fd, char* sub_str);

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDONLY);
    char* sub_str = argv[2];
    wrkin(fd,sub_str);
    return 0;
}

void printcont(int fsize,char* contents, char* sub_str){
    int str_len = strlen(sub_str);
    for (int i = 0; i <= fsize - str_len; ++i) {
        if (memcmp(contents + i, sub_str, str_len) == 0) {
            printf("%d ", i);
        }
    }
}

void wrkin(int fd, char* sub_str){
    struct stat st;
    fstat(fd, &st);
    char* contents = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    printcont(st.st_size, contents,sub_str);
    munmap(contents, st.st_size);
    close(fd);
}