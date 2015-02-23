/*
myHead Tests
Needs to accept -n and -c options
Needs to accept only basic (positive) counts for options
Need not accept dashes for file arguments
Syntax needs to be "myhead [-nN | -cN] [FILE]..."
executable needs to be named myhead
-n and -c options need to accept an integer argument
if no options are given, print 10 lines
argument to options can be immediately adjacent to option e.g. -n25
handle any number of file arguments, including zero
myhead test.text
myhead -n15 test.text
myhead -c50 test.text
myhead
myhead -n15
myhead test1.text test2.text test3.text
myhead -n15 test1.text test2.text test3.text
produce exactly the same output as head with the same options
must include the following functions:
    void head_lines(FILE *fpntr, int lines)
    void head_chars(FILE *fpntr, int chars)
    char *get_next_line(FILE *fpntr)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for getopt

#define MAX_LINE_LENGTH = 100;

void print_args(int argc, char * argv[]);
void head_lines(FILE * fpntr, int lines);
void head_chars(FILE * fpntr, int chars);
char * get_next_line(FILE * fpntr);

// Global State
// Default behaviour is to print 10 lines
int n_option = 10;
int c_option = 0;

int get_option_value(char * opt, int argc, char * argv[])
{
  // Loop through the arguments in argv and look for anything
  // starting with - followed by n or c
  for (int arg = 0; arg < argc; arg++)
  {
    printf("Size of argument: %lu\n", sizeof(argv[arg]));
    if (strncmp(argv[arg], "-n", 8) == 0){
      printf("%s\n", argv[arg]);
    }
  }
  return 0; //Temporary
}

void print_args(int argc, char * argv[])
{
  printf("Number of options: %d\n", argc-1);
  for (int i = 1; i < argc; i++){
    printf("Argument %d: %s\n", i, argv[i]);
  }
}

int main(int argc, char * argv[])
{
    char * opt = "-n";
    print_args(argc, argv);
    n_option = get_option_value(opt, argc, argv);
    exit(EXIT_SUCCESS);
}
