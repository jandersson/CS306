#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <linux/limits.h>

#define PORT 3060
#define SECRET "<CS30615spr>\n"

/* Remcp Protocol

  Client sends <remcp>\n
  Server responds with <remcp>\n
  Client sends secret\n

*/
const char * remcp = "<remcp>\n";
const char * secret = SECRET;
const char * ok = "<ok>\n";
const char * ready = "<ready>\n";
const char * protocol_send = "<send>\n";
const char * error = "<error>\n";

int validate_filepath(char * file_path);

int validate_filepath(char * file_path){

}

int main(void)
{
    char message_buffer[PATH_MAX + 1];
    struct sockaddr_in servaddr;
    int sockfd, connection_fd, nread;

    // Change to home directory
    if (chdir(getenv("HOME")) == -1){
        perror("Unable to switch to home directory");
        exit(EXIT_FAILURE);
    }

    // Create Socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Bind Socket

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

    printf("Server started...\n");
    while(1){
        // Complete connection with listening socket, disregarding client address data
        connection_fd = accept(sockfd, (struct sockaddr *) NULL, NULL);

        // Read <remcp>\n
        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
        message_buffer[nread] = '\0';
        printf("Client says: %s\n", message_buffer);
        if(strcmp(message_buffer, remcp) == 0){
            write(connection_fd, remcp, strlen(remcp));
        }
        else close(connection_fd);

        // Read <secret>\n
        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
        message_buffer[nread] = '\0';
        printf("Client says: %s\n", message_buffer);
        if(strcmp(message_buffer, secret) == 0){
            write(connection_fd, ok, strlen(ok));
        }
        else close(connection_fd);

        // Read file pathname

        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
        message_buffer[nread] = '\0';
        printf("Client says: %s\n", message_buffer);

        close(connection_fd);
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}
