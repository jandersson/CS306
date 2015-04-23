#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


void print_usage(char* program_name);
void command1(char * program_name, int * pipefd);
void command2(char * program_name, int * pipefd);
char** parse(char * command);

char** parse(char * command){
    char** args = malloc(sizeof(char *) * strlen(command));
    int i = 0;
    args[i++] = strtok(command, " ");
    while((args[i++] = strtok(NULL, " ")) != NULL)
    return args;
}

void print_usage(char * program_name){
    fprintf(stderr, "Usage: %s COMMAND1 COMMAND2\n", program_name);
    return;
}

void command1(char * command, int * pipefd){
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    char** args = parse(command);
    execvp(args[0], args);
    fprintf(stderr, "Execution of %s failed\n", args[0]);
    exit(EXIT_SUCCESS);
}

void command2(char * command, int * pipefd){
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    char** args = parse(command);
    execvp(args[0], args);
    fprintf(stderr, "Execution of %s failed\n", args[0]);
    exit(EXIT_SUCCESS);
}

int main(int argc, char * argv[])
{
    if(argc < 3){
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if(pipe(pipefd) == -1){
        perror("Failed to open pipe\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid1;
    switch(pid1 = fork()){
        case -1:
            perror("Fork failed\n");
            exit(EXIT_FAILURE);
        case 0:
            command1(argv[1], pipefd);
            exit(EXIT_SUCCESS);
        default:
            break;
    }
    pid_t pid2;
    switch(pid2 = fork()){
        case -1:
            perror("Fork failed\n");
            exit(EXIT_FAILURE);
        case 0:
            command2(argv[2], pipefd);
            exit(EXIT_SUCCESS);
        default:
            break;
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait();
    wait();
    exit(EXIT_SUCCESS);
}

