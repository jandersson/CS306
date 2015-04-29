#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect();
    exit(EXIT_SUCCESS);
}

