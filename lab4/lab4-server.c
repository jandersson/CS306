#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
int main(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (bind() == -1){
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }
    listen();
    accept();
    exit(EXIT_SUCCESS);
}
