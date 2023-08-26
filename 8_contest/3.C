#include <inttypes.h>
#include <stdio.h>
#include <windows.h>
#include <stdarg.h>
#include <string.h>

void _printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
}

struct Item {
    int value;
    uint32_t next_pointer;
};

typedef struct Item MyItem;

int main(int argc, char** argv)
{
    DWORD readbytes;
    MyItem local;
    local.value = 0;
    local.next_pointer = -1;

    HANDLE in;
    // file to open, open for reading,for shared reading,default protection,only existing file,
    //regular file,no template attributes
    in = CreateFileA(TEXT(argv[1]),GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    // file descriptor,data buffer,number of bytes to read,
    //number of bytes read,asynchronous buffer
    ReadFile(in,&local,sizeof local,&readbytes,0);

    if (readbytes <= 0) {
        return 0;
    }

    while (local.next_pointer != 0) {
       char str[100];
        sprintf(str, "%d\n", local.value);
        str[strlen(str)] - '\0';
        write(1, str, strlen(str));
        // SetFilePointer moves the position pointer in the open file
        // file descriptor,pointer move bytes, pointer move bytes,reference point is the beginning of the file
        SetFilePointer(in,local.next_pointer,0,0);

        ReadFile(in, &local, sizeof local, &readbytes, 0);
    }
    char str[100];
    sprintf(str, "%d\n", local.value);
    str[strlen(str)] - '\0';
    write(1, str, strlen(str));
    CloseHandle(in);
}