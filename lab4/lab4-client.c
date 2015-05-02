#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

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

    if (argc < 2){
        perror("Invalid number of arguments\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    char * server_ip = argv[1];

    char * msg = "Hello server from client\n";
    // TODO: Usage print function
    // TODO: print error message for file not readable, if its readable, get <ready> back
    int sockfd, connection_fd;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_aton(server_ip, &servaddr.sin_addr);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }
    connection_fd = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    write(connection_fd, remcp, strlen(remcp));
    close(connection_fd);
    exit(EXIT_SUCCESS);
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s IP_ADDRESS:FILE_NAME\n", program_name);
}
