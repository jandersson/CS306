#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/limits.h>
#define PORT 3060
#define SECRET "<CS30615spr>\n"

const char * remcp = "<remcp>\n";
const char * secret = SECRET;
const char * ok = "<ok>\n";
const char * ready = "<ready>\n";
const char * protocol_send = "<send>\n";
const char * error = "<error>\n";

void print_usage(char * program_name);

int main(int argc, char * argv[])
{
    int nread = 0;
    char message_buffer[PATH_MAX];
    char * file_path = NULL;
    char * file_name = NULL;
    char * strtok_token = NULL;
    char * server_ip = NULL;
    FILE * file_copy = NULL;
    int sockfd = 0;
    struct sockaddr_in servaddr;

    // Validate command line arguments and retrieve server IP and file path

    if (argc < 2){
        fprintf(stderr, "Invalid number of arguments\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("first copy\n");
    server_ip = strtok(argv[1], ":");
    printf("server ip: %s\n", server_ip);
    if ( (file_path = strtok(NULL, ":")) == NULL){
        fprintf(stderr, "Invalid argument format\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else{
        // Allocate memory for the file name and copy the path into it since strtok modifies strings
        file_name = malloc(strlen(file_path + 1));
        strcpy(file_name, file_path);
    }
    printf("File path: %s\n", file_path);
    printf("File name: %s\n", file_name);
    // Extract file name from path if nested
    file_name = strtok(file_name, "/");
    while( (strtok_token = strtok(NULL, "/")) != NULL){
        file_name = strtok_token;
    }
    printf("File path: %s\n", file_path);
    printf("File name: %s\n", file_name);
    // Setup socket data structures
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

    // Send <remcp>
    write(sockfd, remcp, strlen(remcp));
    nread = read(sockfd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Server says: %s\n", message_buffer);

    // Send <secret>
    if (strcmp(message_buffer, remcp) == 0){
        write(sockfd, secret, strlen(secret));
    }
    else{
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    nread = read(sockfd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Server says: %s\n", message_buffer);

    // Send pathname

    if (strcmp(message_buffer, ok) == 0){
        write(sockfd, file_path, strlen(file_path));
    }
    else{
        fprintf(stderr, "Remcp protocol error\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Check for <error> from server, if found, terminate client
    nread = read(sockfd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Server says: %s\n", message_buffer);
    if (strcmp(message_buffer, error) == 0){
        fprintf(stderr, "Requested file not found\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Check for <ready> from server, if found, create file for copying and send <send>
    if(strcmp(message_buffer, ready) == 0){

        if( (file_copy = fopen(file_name, "wb")) == NULL ){
            perror("Error opening file for writing");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        write(sockfd, protocol_send, strlen(protocol_send));
    }
    while((nread = read(sockfd, message_buffer, sizeof(message_buffer))) > 0){
        fwrite(message_buffer, 1, nread, file_copy);
    }

    close(sockfd);
    exit(EXIT_SUCCESS);
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s IP_ADDRESS:FILE_NAME\n", program_name);
}
