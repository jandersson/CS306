//----------------------------------------------------
// (1) Write a C function that uses C library I/O to determine the number
// of lines in a text file:
// -- The function prototype is: int num_lines(char *file)
// -- Returns the number of lines in the file
// -- Ignore error checking (and chances of errors)
// -- Function must be self-contained (cannot call other user functions)

#include <stdio.h>

int num_lines(char * file);

int num_lines(char * file){
  char buffer[100];
  FILE * fstream = fopen(file, "r");
  int lineCount = 0;
  char * line = NULL;
  while((line = fgets(buffer, 100, fstream)) != NULL){
    ++lineCount;
  }

  fclose(fstream);
  return lineCount;
}

int main(int argc, char * argv[]){
    int lineCount = num_lines(argv[1]);
    printf("# of lines: %i", lineCount);
}
