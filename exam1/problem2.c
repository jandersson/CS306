// (2) Write a C program (main) that uses C library I/O to find the length
// of the longest line in a file, and print it to standard output:
// -- The call syntax is: maxlength FILE_PATH
// -- Must worry about error checking call and all library functions.
// -- Return either EXIT_SUCCESS or EXIT_FAILURE as appropriate.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[]){

  if(argc != 2){
    printf("Usage: %s FILE_PATH\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char * file_path = argv[1];
  FILE * fstream = NULL;

  if((fstream = fopen(file_path, "r")) == NULL){
    fprintf(stderr, "DANGER: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int line_length, max_length, next_char = 0;
  int num_lines = 0;
  fstream = fopen(file_path, "r");

  while((next_char = fgetc(fstream)) != EOF){
    if(next_char == '\n'){
      num_lines++;
      if(line_length > max_length) max_length = line_length;
      line_length = 0;
    }
    else line_length++;
  }
  if(line_length > max_length) max_length = line_length;
  if(!ferror(fstream)){
    printf("Max line length: %i\n", max_length);
    fclose(fstream);
    exit(EXIT_SUCCESS);
  }
  else{
    fclose(fstream);
    exit(EXIT_FAILURE);
  }
}
