#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <linux/limits.h>

#define PORT 3060
#define SECRET "CS30615spr"

/* Remcp Protocol

  Client sends <remcp>\n
  Server responds with <remcp>\n
  Client sends secret\n

*/
const char * remcp = "<remcp>\n";
const char * secret = "<JAA>\n";
const char * ok = "<ok>\n";
const char * ready = "<ready>\n";
const char * protocol_send = "<send>\n";
const char * error = "<error>\n";

int main(void)
{
    char message_buffer[PATH_MAX];
    // Create Socket
    int sockfd, connection_fd, nread;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Bind Socket
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
        perror("Could not bind socket\n");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if(listen(sockfd, 10) == -1){
        perror("Unable to listen for connections\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        // Complete connection with listening socket, disregarding client address data
        printf("Starting server\n");
        connection_fd = accept(sockfd, (struct sockaddr *) NULL, NULL);
        printf("Connection created\n");
        nread = read(sockfd, message_buffer, sizeof(message_buffer));
        printf("nread: %i\n", nread);
        message_buffer[nread] = '\0';
        printf("Client says: %s\n", message_buffer);
        write(sockfd, remcp, strlen(remcp));
        close(connection_fd);
        close(sockfd);
    }

    exit(EXIT_SUCCESS);
}
