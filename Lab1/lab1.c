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

#define MAX_LINE_LENGTH 100

void print_args(int argc, char * argv[]);
void head_lines(FILE * fpntr, int lines);
void head_chars(FILE * fpntr, int chars);
char * get_next_line(FILE * fpntr);
int decode_options(char * opts_to_find, int argc, char * argv[]);
void read_file(char * file_name);
void print_usage(char * argv[]);
// Global State
// Default behaviour is to print 10 lines
int n_option = 10;
int c_option = 0;

void print_usage(char * argv[])
{
  printf("Usage: %s [-n #] [-c #]\n", argv[0]);
}

void read_file(char * file_name)
{
  char buffer[MAX_LINE_LENGTH];
  FILE * fptr = fopen(file_name, "r");
  fclose(fptr);
}

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
  int opt, _optind;
  while ((opt = getopt(argc, argv, opts_to_find)) != -1)
  {
    _optind = optind;
    printf("optind: %i\n", _optind);
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
        print_usage(argv);
        exit(EXIT_FAILURE);
    }
  }
  printf("Whats in argv[%d]?\n", _optind);
  printf("Probably a segfault, dummy\n");
  printf("argc: %i, optind: %i\n", argc, optind);
  int number_file_inputs;
  int first_file_index = 0;
  number_file_inputs = argc - optind;
  if ((number_file_inputs) > 0)
  {
    first_file_index = optind;
  }
  printf("%d files were specified\n", number_file_inputs);
  printf("%d is the index of the first file\n", first_file_index);

  return first_file_index;
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
    print_usage(argv);
    int file_ind;
    char * opts_to_find = "n:c:";
    file_ind = decode_options(opts_to_find, argc, argv);
    if (file_ind == 0)
    {
      // If no file is specified, the index will be 0 and the program
      // should terminate
      exit(EXIT_FAILURE);
    }
    printf("file_ind: %d\n", file_ind);
    printf("argv[%d]: %s\n", file_ind, argv[file_ind]);
    read_file(argv[file_ind]);
    exit(EXIT_SUCCESS);
}
