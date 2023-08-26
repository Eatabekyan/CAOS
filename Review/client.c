#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/limits.h>

int main(int argc, char* argv[]) {
	uint16_t port = htons(atoi(argv[1]));
    char test[PATH_MAX];
    memset(test, 0, sizeof(test));
    memcpy(test, "abc def f", sizeof("abc def f"));
	char buffer[4 * PATH_MAX];
	memset(buffer, 0, sizeof(buffer));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket problem");
		exit(1);
	}
	int connected;
	if ((connected = connect(sockfd, (struct sockaddr*)(&addr), sizeof(struct sockaddr_in))) == -1) {
		close(sockfd);
		perror("connect problem");
		exit(1);
	}
	write(sockfd, test, sizeof(test));
    while (read(sockfd, buffer, sizeof(buffer)) > 0) {
        printf("%s", buffer);
    }
	close(sockfd);
	return 0;
}
