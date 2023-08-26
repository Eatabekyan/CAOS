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

int GetSocket() {
    int answer = -1;
    if ((answer = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket problem");
        exit(1);
    }
    return answer;
}

void TryToBind(int sockfd, struct sockaddr_in* address) {
    if (bind(sockfd, (struct sockaddr*)(address), sizeof(struct sockaddr)) == -1) {
        perror("bind problem");
        exit(1);
    }
}

void ServerSocket(int sockfd) {
    if (listen(sockfd, SOMAXCONN) == -1) {
        perror("listen problem");
        exit(1);
    }
}

void ClientProcessing(struct sockaddr_in* client, int client_sockfd, int sockfd, socklen_t length) {
    ssize_t message_length;
    char buffer[4 * PATH_MAX];
    memset(buffer, 0, sizeof(buffer));
    client_sockfd = accept(sockfd, (struct sockaddr*)(client), &length);
    if (client_sockfd == -1) {
        perror("accept problem");
        exit(1);
    }
    message_length = read(client_sockfd, buffer, sizeof(buffer));
    char result[100];
    memset(result, 0, sizeof(result));
    size_t length = 0;
    char* token = strtok(buffer, " ");
    while (token != NULL) {
        memcpy(result + length, token, sizeof(token));
        length += strlen(token);
        result[length] = '\n';
        ++length;
        token = strtok(NULL, " ");
    }
    write(client_sockfd, result, length);
    close(client_sockfd);
    close(sockfd);
}
int main(int argc, char* argv[]) {
    int64_t port_num = strtol(argv[1], NULL, 10);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port_num);
    char* server_answer = "Welcome to Kazakhstan\n";
    int sockfd = GetSocket();
    TryToBind(sockfd, &address);
    ServerSocket(sockfd);
    
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int client_socket = -1;
    
    ClientProcessing(&client, client_socket, sockfd, len);
    printf("%s", server_answer);
    return 0;
}
