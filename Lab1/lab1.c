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

TODO: Capture input from stdin when no files are given
 */
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100


// Function Prototypes


void print_args(int argc, char * argv[]);
void head_lines(FILE * fpntr, int lines);
void head_chars(FILE * fpntr, int chars);
char * get_next_line(FILE * fpntr);
int decode_options(char * opts_to_find, int argc, char * argv[], int c_option,int n_option);
FILE * get_stream(char * file_name);
void print_usage(char * argv[]);


// Global State

// TODO: Get rid of these global vars
// Default behaviour is to print 10 lines
// Specifies the number of lines to print from the file
// int n_option = 10;
// Specifies the number of bytes to print from the file
// int c_option = 0;


// Display related functions


void print_usage(char * argv[])
{
  printf("Usage: %s [-n # | -c #] {FILE}\n", argv[0]);
}


void print_args(int argc, char * argv[])
{
  printf("Number of options: %d\n", argc-1);
  for (int i = 1; i < argc; i++)
  {
    printf("Argument %d: %s\n", i, argv[i]);
  }
}


// Required functions


void head_chars(FILE * fpntr, int chars)
{
  int chars_iter = 0;
  int c;
  // if (fpntr == stdin)
  // {
  //   chars == INT_MAX;
  // }
  // if (fpntr == stdin)
  // {
  //   while ((c = fgetc(fpntr)) != EOF)
  //   {
  //     printf("%c",c);
  //   }
  // }
  // else
  // {
    while ((c = fgetc(fpntr)) != EOF && chars_iter < chars)
    {
      printf("%c",c);
      chars_iter++;
    }
  // }
  fclose(fpntr);
}


void head_lines(FILE * fpntr, int lines)
{

}


char * get_next_line(FILE * fpntr)
{
  static char buff[MAX_LINE_LENGTH];
  fgets(buff, 100, fpntr); //CHANGE THIS
  return buff;
}


// Helper functions


FILE * get_stream(char * file_name)
{
  // Will produce a segfault if the file does not exist
  // head checks for a file existing, if not prints:
  //    head: cannot open ‘filename.txt’ for reading: No such file or directory
  char buffer[MAX_LINE_LENGTH];
  int c;
  FILE * fptr;

  if (((fptr = fopen(file_name, "r")) == NULL))
  {
    fprintf(stderr, "Error: No such file");
  }
  else
  {
    FILE * fptr = fopen(file_name, "r");
  }
  return fptr;
}


int decode_options(char * opts_to_find, int argc, char * argv[], int c_option, int n_option)
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


int main(int argc, char * argv[])
{
  //Determine if there are file arguments
    int file_ind, ok, c_option;
    int n_option = 10;
    FILE * file;
    char * opts_to_find = "n:c:";
    file_ind = decode_options(opts_to_find, argc, argv, c_option, n_option);
    if (file_ind == 0)
    {
      // If no file is specified, the index will be 0 and the program
      // should read from standard input
      file = stdin;
      head_chars(file, c_option);
    }
    // Loop through file args
    // Prints the first file: printf("argv[%d]: %s\n", file_ind, argv[file_ind]);
    file = get_stream(argv[file_ind]);
    //head_lines logic
    for (int i = 0; i < n_option; i++)
    {
      printf("Line#%i: %s", i+1, get_next_line(file));
    }

    head_chars(file, c_option);
    exit(EXIT_SUCCESS);
}
