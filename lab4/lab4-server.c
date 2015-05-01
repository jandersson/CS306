#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 3060

int main(void)
{

    // Create Socket
    int sockfd, connection_fd;
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
        perror("Could not bind socket");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if(listen(sockfd, 10) == -1){
        perror("Unable to listen for connections");
        exit(EXIT_FAILURE);
    }

    // Complete connection with listening socket, disregarding client address data
    connection_fd = accept(sockfd, NULL, NULL);
    exit(EXIT_SUCCESS);
}
