#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 3060
#define SECRET "CS30615spr"

void print_usage(char * program_name);

int main(int argc, char * argv[])
{

    char * msg = "Hello server from client";
    // TODO: Usage print function
    // TODO: print error message for file not readable, if its readable, get <ready> back
    int sockfd, connection_fd;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &servaddr.sin_addr);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }
    connection_fd = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    write(connection_fd, msg, strlen(msg));
    close(connection_fd);
    exit(EXIT_SUCCESS);
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s IP_ADDRESS:FILE_NAME", program_name);
}
