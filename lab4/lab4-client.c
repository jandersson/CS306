#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/limits.h>
#define PORT 3060
#define SECRET "CS30615spr"

const char * remcp = "<remcp>\n";
const char * secret = "<JAA>\n";
const char * ok = "<ok>\n";
const char * ready = "<ready>\n";
const char * protocol_send = "<send>\n";
const char * error = "<error>\n";

void print_usage(char * program_name);

int main(int argc, char * argv[])
{
    int nread = 0;
    char message_buffer[PATH_MAX];
    if (argc < 2){
        perror("Invalid number of arguments\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    char * server_ip = argv[1];

    char * msg = "Hello server from client\n";
    // TODO: print error message for file not readable, if its readable, get <ready> back
    int sockfd;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton(server_ip, &servaddr.sin_addr);

    // Create Socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Connect to Server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("Error creating connection socket");
        exit(EXIT_FAILURE);
    }

    printf("remcp: %s\n", remcp);
    printf("strlen(remcp): %i\n", strlen(remcp));
    write(sockfd, remcp, strlen(remcp));
    nread = read(sockfd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Server says: %s\n", message_buffer);
    close(sockfd);
    exit(EXIT_SUCCESS);
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s IP_ADDRESS:FILE_NAME\n", program_name);
}
