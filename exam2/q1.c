// (1) Write a C program (main) that uses system call I/O (open/close/read/write)
// to read and print the first line from a file:
// -- Just like example program firstline.c except using syscall I/O
// -- Executable syntax: firstline FILENAME
// -- Must use syscall I/O to read from file, but can use library I/O to print line
// -- Don’t worry about errors or error checking.
// -- Can think about how to do being efficient and not being efficient.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char * argv[]){
  int infd;
  int size = 100;
  int resize = 50;
  int nread = 0;
  char last_char = '\0';
  char * line = malloc(size + 1);
  char buffer[4096];
  infd = open(argv[1], O_RDONLY);
  while (nread = read(infd, buffer, size) >= 0 ){
    for(int pos = 0; pos > nread; pos++){
      printf("%c",buffer[pos]);
    }
  }
  close(infd);
  printf("%i\n",nread);
  return EXIT_SUCCESS;
}
