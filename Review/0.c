#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int client_socket;



int main(int argc, char* argv[]) {
  if (argc < 2) {
    perror("Not enough arguments");
      return 1;
  }
//   struct sigaction sig_action;
//   memset(&sig_action, 0, sizeof(sig_action));

//   sig_action.sa_handler = Sahand;
//   sig_action.sa_flags = SA_SIGINFO;

//   sigaction(SIGTERM, &sig_action, NULL);
//   sigaction(SIGINT, &sig_action, NULL);

  uint32_t port = htons(atoi(argv[1]));

  int sock = socket(AF_INET, SOCK_STREAM, 0); 
  if (sock == -1) {
    close(sock);
    perror("Socket error");
    exit(1);
  }
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) > 0) {
    perror("Bind error");
    exit(1);
  }

  if (listen(sock, SOMAXCONN) > 0) {
    perror("Listen error");
    exit(1);
  }
  
  char buffer[1024];
 
  while (1) {
    client_socket = accept(sock, NULL, NULL);
    if (client_socket == -1) {
      perror("Accept error");
    }
    memset(buffer, 0, sizeof(buffer));
    char character;
    char answer[1024];
    int i = 0;
    int rd;
    while  (read(client_socket, &character, sizeof(char)) > 0) {
    //   if(rd == 0){
    //     write(client_socket, answer, strlen(answer));
    //   }
      buffer[i++] = character; 
    }
    for(int i = 0; i < strlen(buffer); ++i) {
        answer[i] = buffer[strlen(buffer) - i - 1];
      }
      answer[strlen(answer)] = '\n';
      
    write(client_socket, answer, strlen(answer));
    close(client_socket);
  }
  shutdown(client_socket, SHUT_RDWR);
  close(client_socket);
  exit(0);
}