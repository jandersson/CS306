//    (1) Write a C program (main) that will create a file, start a function that
//    can write to the file running in a child process, then wait for the function
//    (really the subprocess) to complete (terminate):
//    -- The file to be created should be named output.
//    -- The prototype for the function is: void process(int filefd)
//    -- filefd must be a file descriptor that process() will use to write to the file.
//    -- Error check the fork() call, and terminate if it fails.
//    -- process() will eventually exit() and indicate success/failure via its exit status.
//    -- Your program must not terminate until the child has terminated;
//    don’t leave orphans/zombies.
//    -- If the child indicates failure exit status, your program should too.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int process(int filefd);

int process(int filefd){
    char * write_str = "Write this string to a file!\n";
    //char * file_buff = malloc(strlen(write_str));
    write(filefd, write_str, sizeof(write_str));
    exit(EXIT_SUCCESS);
}

int main(void)
{
    char * file_name = "output";
    int open_file_fd;
    pid_t proc_id;

    int ok = 1;

    open_file_fd = open(file_name, O_WRONLY | O_CREAT);

    switch(proc_id = fork()){
    case -1:
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    case 0:
        process(open_file_fd);
    case 1:
        break;
    }
    ok = wait();
    if(ok == -1){
        exit(EXIT_FAILURE);
    }
    else exit(EXIT_SUCCESS);
}

