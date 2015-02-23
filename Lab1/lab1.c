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
  //  This function will:
  //    Decode the command line arguments using the getopt function
  //    For personal reference the opts_to_find is a string with
  //    the characters to look for. A ":" adjacent to a character
  //    indicates that it has required arguments and will store the arguments
  //    in the string "optarg"
  //  This function takes:
  //    opts_to_find: a string of options to look for
  //    argc, argv: command line argument list and count
  //  This function returns:
  //    an integer
  int opt;
  while ((opt = getopt(argc, argv, opts_to_find)) != -1)
  {
    switch(opt)
    {
      case 'n':
        printf("Option -n\n");
        n_option = atoi(optarg);
        printf("n's argument: %i\n", n_option);
        break;
      case 'c':
        printf("Option -c\n");
        c_option = atoi(optarg);
        printf("c's argument: %i\n", c_option);
        break;
      default:
        printf("Usage: %s", argv[0]);
        exit(EXIT_FAILURE);
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
    char * opts_to_find = "n:c:";
    decode_options(opts_to_find, argc, argv);
    exit(EXIT_SUCCESS);
}
