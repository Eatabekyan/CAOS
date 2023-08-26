#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;

void Printing(int fd, off_t sz){
    char* contents = mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    Item* item = (Item*)contents;
    printf("%i ", item->value);
    while (item->next_pointer != 0) {
        item = (Item*)(contents + item->next_pointer);
        printf("%i ", item->value);
    }
    munmap(contents, sz);
}

int wrking(int fd){
    off_t sz = lseek(fd, 0, SEEK_END);
    if (sz == 0) {
        return 1;
    }
    lseek(fd, 0, SEEK_SET);
    Printing(fd,sz);
    return 0;
}



int main(int argc, char** argv)
{
    return wrking(open(argv[1], O_RDONLY));
}
