//! A head copy-cat
/*!
  This program attempts to implement the functionality of the GNU head program
*/

/*
myHead Tests
Needs to accept -n and -c options
Needs to accept only basic (positive) counts for options
Need not accept dashes for file arguments
Syntax needs to be "myhead [-nN | -cN] [FILE]..."
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

// Global State
//This variable will enable various code tracing functionality
int debug = 1;
// Function Prototypes


void print_args(int argc, char * argv[]);
void head_lines(FILE * fpntr, int lines);
void head_chars(FILE * fpntr, int * chars);
char * get_next_line(FILE * fpntr);
int decode_options(char * opts_to_find, int argc, char * argv[], int * c_option,int * n_option);
FILE * get_stream(char * file_name);
void print_usage(char * argv[]);

// Display related functions

void print_usage(char * argv[]){
  printf("Usage: %s [-n # | -c #] {FILE}\n", argv[0]);
}

void print_args(int argc, char * argv[]){
  printf("Number of options: %d\n", argc-1);
  for (int i = 1; i < argc; i++){
    printf("Argument %d: %s\n", i, argv[i]);
  }
}


// Required functions


void head_chars(FILE * fpntr, int * chars){
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
    while ((c = fgetc(fpntr)) != EOF && chars_iter < *chars)
    {
      printf("%c",c);
      chars_iter++;
    }
  // }
  fclose(fpntr);
}


void head_lines(FILE * fpntr, int lines){
  for (int i = 0; i < lines; i++){
    printf("Line#%i: %s", i+1, get_next_line(fpntr));
  }
}


char * get_next_line(FILE * fpntr){
  static char buff[MAX_LINE_LENGTH];
  fgets(buff, 100, fpntr); //CHANGE THIS
  return buff;
}


// Helper functions


FILE * get_stream(char * file_name)
{
  //! Opens given file and returns a file stream after performing error checking
  // Will produce a segfault if the file does not exist
  // head checks for a file existing, if not prints:
  //    head: cannot open ‘filename.txt’ for reading: No such file or directory
  char buffer[MAX_LINE_LENGTH];
  int c;
  FILE * fptr = NULL;

  if (((fptr = fopen(file_name, "r")) == NULL)){
    fprintf(stderr, "myhead: cannot open '%s' for reading: No such file or directory\n", file_name);
  }
  else{
    FILE * fptr = fopen(file_name, "r");
  }
  return fptr;
}


int decode_options(char * opts_to_find, int argc, char * argv[], int * c_option, int * n_option)
{
  //! Decodes the options given from the command line and returns the index of the
  //! first file in argv.
  int opt, _optind;
  while ((opt = getopt(argc, argv, opts_to_find)) != -1)
  {
    _optind = optind;
    switch(opt)
    {
      case 'n':
        *n_option = atoi(optarg);
        break;
      case 'c':
        *c_option = atoi(optarg);
        break;
      default:
        print_usage(argv);
        exit(EXIT_FAILURE);
    }
  }
  int number_file_inputs;
  int first_file_index = 0;
  number_file_inputs = argc - optind;
  if ((number_file_inputs) > 0){
    first_file_index = optind;
  }
  //! Tracing Code
  if(debug == 1){
    printf("-c argument: %i\n", *c_option);
    printf("-n argument: %i\n", *n_option);
    printf("Files specified: %d\n", number_file_inputs);
    printf("1st File Index: %d\n", first_file_index);
  }
  return first_file_index;
}


int main(int argc, char * argv[])
{
  //! Main function takes command line parameters and an implicit argument count, returns
  //! an exit code.
  // c_option tracks the value of the amount of characters to read from -c option
  // file_ind tracks the index in argv of the first file argument
  // n_option tracks the value of the amount of lines to read from the -n option
  // ok is a flag raised when an error occurs and used to exit with appropriate exit status
  int file_ind  = 0, c_option = 0, ok = 1;
  int n_option = 10;
  FILE * file;
  char * opts_to_find = "n:c:";
  //! Tracing Code
  if(debug == 1){
    printf("argc: %i\n", argc);
  }
  //! Decode the command line arguments, get the number of lines/chars to print
  //! and the index of the first file argument
  file_ind = decode_options(opts_to_find, argc, argv, &c_option, &n_option);
  if (file_ind == 0){
    // If no file is specified, the index will be 0 and the program
    // should read from standard input
    file = stdin;
    head_chars(file, &c_option);
  }
  // Dev Hint #2: Loop through file arguments calling fopen() with error checking and print out the file
  //! Loop through file args
  for (int i = file_ind; i < argc; i++){
    // Need to print a header if there are multiple files:
    // head does this:
    // ==> filename <==
    file = get_stream(argv[i]);
    if (file != NULL){
      printf("==> %s <==\n", argv[i]);
      head_lines(file, n_option);
    }
    else{
      ok = 0;
    }
  }
  // Prints the first file: printf("argv[%d]: %s\n", file_ind, argv[file_ind]);
  //head_chars(file, &c_option);
  if (ok == 1){
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}
