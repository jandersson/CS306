#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 3060
#define SECRET "JAA"

void print_usage(char * program_name);

int main(void)
{
    // Permissions don't matter
    // TODO: Usage print function
    // TODO: print error message for file not readable, if its readable, get <ready> back
    int sockfd;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &servaddr.sin_addr);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    exit(EXIT_SUCCESS);
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s IP_ADDRESS:FILE_NAME", program_name);
}
