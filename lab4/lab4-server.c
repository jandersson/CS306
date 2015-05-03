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
  Server responds <ok>\n if <secret> is correct
  Client sends file path
  Server checks file path, sends <error> if not valid

*/
const char * remcp = "<remcp>\n";
const char * secret = SECRET;
const char * ok = "<ok>\n";
const char * ready = "<ready>\n";
const char * protocol_send = "<send>\n";
const char * error = "<error>\n";

void handle_client(int connection_fd);

void handle_client(int connection_fd){
    char file_data[4096];
    char message_buffer[PATH_MAX + 1];
    FILE * target_file = NULL;
    char * file_path = NULL;
    size_t bytes_read;
    int nread, bytes_sent;
    // Read <remcp>\n
    nread = read(connection_fd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Client says: %s\n", message_buffer);
    // If client sent <remcp>, send <remcp>, otherwise terminate connection
    if(strcmp(message_buffer, remcp) == 0){
        send(connection_fd, remcp, strlen(remcp), 0);
    }
    else close(connection_fd);

    // Read <secret>\n
    nread = read(connection_fd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Client says: %s\n", message_buffer);
    // If secret is right, send <ok>, otherwise terminate connection
    if(strcmp(message_buffer, secret) == 0){
        write(connection_fd, ok, strlen(ok));
    }
    else close(connection_fd);

    // Read file pathname
    nread = read(connection_fd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Client says: %s\n", message_buffer);
    file_path = message_buffer;
    // Try to open the specified file, if invalid send error and terminate the connection
    if ((target_file = fopen(file_path, "rb")) == NULL){
        write(connection_fd, error, strlen(error));
        fclose(target_file);
        close(connection_fd);
    }
    else{
        // File exists, send <ready>
        write(connection_fd, ready, strlen(ready));
    }

    // Read <send> and send the file
    nread = read(connection_fd, message_buffer, sizeof(message_buffer));
    message_buffer[nread] = '\0';
    printf("Client says: %s\n", message_buffer);
    if (strcmp(message_buffer, protocol_send) == 0){
        // loop through the file, reading blocks, sending them to the client
        while( (bytes_read = fread(file_data, sizeof(char), 4096, target_file)) > 0 ){
            bytes_sent = send(connection_fd, file_data, bytes_read, 0);
        }
        fclose(target_file);
        close(connection_fd);
    }
    else{
        write(connection_fd, error, strlen(error));
        fclose(target_file);
        close(connection_fd);
    }
}

int main(void)
{
    struct sockaddr_in servaddr;
    int sockfd, connection_fd;

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
        perror("Could not bind socket");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if(listen(sockfd, 10) == -1){
        perror("Unable to listen for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server started...\n");
    while(1){
        // Complete connection with listening socket, disregarding client address data
        connection_fd = accept(sockfd, (struct sockaddr *) NULL, NULL);
        handle_client(connection_fd);

//        // Read <remcp>\n
//        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
//        message_buffer[nread] = '\0';
//        printf("Client says: %s\n", message_buffer);
//        // If client sent <remcp>, send <remcp>, otherwise terminate connection
//        if(strcmp(message_buffer, remcp) == 0){
//            send(connection_fd, remcp, strlen(remcp), 0);
//        }
//        else close(connection_fd);

//        // Read <secret>\n
//        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
//        message_buffer[nread] = '\0';
//        printf("Client says: %s\n", message_buffer);
//        // If secret is right, send <ok>, otherwise terminate connection
//        if(strcmp(message_buffer, secret) == 0){
//            write(connection_fd, ok, strlen(ok));
//        }
//        else close(connection_fd);

//        // Read file pathname
//        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
//        message_buffer[nread] = '\0';
//        printf("Client says: %s\n", message_buffer);
//        file_path = message_buffer;
//        // Try to open the specified file, if invalid send error and terminate the connection
//        if ((target_file = fopen(file_path, "rb")) == NULL){
//            write(connection_fd, error, strlen(error));
//            fclose(target_file);
//            close(connection_fd);
//        }
//        else{
//            // File exists, send <ready>
//            write(connection_fd, ready, strlen(ready));
//        }

//        // Read <send> and send the file
//        nread = read(connection_fd, message_buffer, sizeof(message_buffer));
//        message_buffer[nread] = '\0';
//        printf("Client says: %s\n", message_buffer);
//        if (strcmp(message_buffer, protocol_send) == 0){
//            // loop through the file, reading blocks, sending them to the client
//            while( (bytes_read = fread(file_data, sizeof(char), 4096, target_file)) > 0 ){
//                bytes_sent = send(connection_fd, file_data, bytes_read, 0);
//            }
//            fclose(target_file);
//            close(connection_fd);
//        }
//        else{
//            write(connection_fd, error, strlen(error));
//            fclose(target_file);
//            close(connection_fd);
//        }

    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}
