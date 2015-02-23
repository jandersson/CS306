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
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH = 100;

void print_args(int argc, char * argv[]);
void head_lines(FILE * fpntr, int lines);
void head_chars(FILE * fpntr, int chars);
char * get_next_line(FILE * fpntr);
int decode_options(char * opts_to_find, int argc, char * argv[]);

// Global State
// Default behaviour is to print 10 lines
int n_option = 10;
int c_option = 0;

int decode_options(char * opts_to_find, int argc, char * argv[])
{
  // Loop through the arguments in argv and look for anything
  // starting with - followed by n or c
  int opt;
  while ((opt = getopt(argc, argv, opts_to_find)) != -1)
  {
    switch(opt)
    {
      case 'n':
        printf("I Gots an n :B!!");
        break;
    }
  }
  return 0; //Temporary
}

void print_args(int argc, char * argv[])
{
  printf("Number of options: %d\n", argc-1);
  for (int i = 1; i < argc; i++)
  {
    printf("Argument %d: %s\n", i, argv[i]);
  }
}

int main(int argc, char * argv[])
{
    char * opts_to_find = "nc:";
    decode_options(opts_to_find, argc, argv);
    exit(EXIT_SUCCESS);
}
