#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int write_bytes(int fd, char* buffer, int to_write);

int main(int argc, char** argv)
{
    char read_buf[4096];
    char buf[4096];
    int i;
    ssize_t currently_read;
    int check, check_write;
    int in, out;
    in = open(argv[1], O_RDONLY);

    int count = (in == -1) + (errno == ENOENT);
    if (count == 2) {
        return 1;
    }
    if (count == 1) {
        return 2;
    }

    out = open(argv[2], O_CREAT | O_WRONLY, 0640);

    if (out == -1) {
        return 2;
    }

    while (1) {
        for (size_t bytes_read = 0; bytes_read < 4096;) {
            currently_read = read(in, read_buf + bytes_read, 4096 - bytes_read);

            if (currently_read == -1) {
                check = -1;
                break;
            }
            if (currently_read == 0) {
                check = bytes_read;
                break;
            }
            bytes_read += currently_read;
        }

        if (check == 0) {
            break;
        }
        i = 0;
        while (i < check) {
            buf[i] = read_buf[check-i];
            ++i;
        }

        check_write = write_bytes(out, buf, i);
        if (check_write == -1)
            return 3;
    }

    close(in);
    close(out);
}

int write_bytes(int fd, char* buffer, int to_write)
{
    size_t bytes_written = 0;
    ssize_t currently_written;
    lseek(fd, 0, SEEK_SET);
    while (bytes_written < to_write) {
        currently_written =
            write(fd, buffer + bytes_written, to_write - bytes_written);
        if (currently_written == -1) {
            return -1;
        }
        bytes_written += currently_written;
    }
    return to_write;
}