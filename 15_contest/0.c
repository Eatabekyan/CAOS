#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    struct in_addr in_addr;
    in_addr.s_addr = inet_addr(argv[1]);

    struct sockaddr_in addr = {.sin_family = AF_INET,
                               .sin_addr = in_addr,
                               .sin_port = htons(atoi(argv[2]))
                              };

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 == connect(sock, (struct sockaddr*)&addr, sizeof addr)) {
        int val = 0;
        if (scanf("%d", &val) > 0) {
            do {
                int got_value;
                int res = write(sock, &val, sizeof(int));
                if (res > 0) {
                    res = read(sock, &got_value, sizeof(int));
                    if (res <= 0)
                        break;
                } else break;
                printf("%i\n", got_value);
            } while (scanf("%i", &val) > 0);
        }
    } else {
        perror("Connection error");
        return 1;
    }
    return 0;
}