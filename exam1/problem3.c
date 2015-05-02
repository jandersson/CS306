// (3) Write a C program (main) that uses C library I/O to create a copy
// of a file:
// -- The call syntax is: mycp SOURCE [TARGET]
// -- If TARGET is not supplied, use TARGET of SOURCE.copy
// -- Try to be as efficient as possible copying

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char * argv[]){
  if(argc != 2){
    printf("argc: %i", argc);
    fprintf(stderr, "Usage: %s SOURCE [TARGET]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char file_target[100] = {0};
  char * file_source = argv[1];
  if(argc == 3){
    snprintf(file_target, 100, "%s.copy", argv[2]);
  }
  else snprintf(file_target,100, "%s.copy", argv[1]);
  printf("%s\n", file_target);
  exit(EXIT_SUCCESS);
}
