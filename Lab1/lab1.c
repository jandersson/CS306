//! A head copy-cat
/*!
  This program attempts to implement the functionality of the GNU head program
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


void head_chars(FILE * fpntr, int chars){
  int chars_iter = 0;
  int c;
    while ((c = fgetc(fpntr)) != EOF && chars_iter < chars){
      printf("%c",c);
      chars_iter++;
    }
  fclose(fpntr);
}

void head_lines(FILE * fpntr, int lines){
  for (int i = 0; i < lines; i++){
    char * line = get_next_line(fpntr);
    if (line != NULL){
      printf("%s\n", line);
    }
    else{
      break;
    }
  }
}


char * get_next_line(FILE * fpntr){
  static char buff[MAX_LINE_LENGTH];
  int pos = 0, next = 0;
  while ((next = fgetc(fpntr)) != '\n' && next != EOF && pos < MAX_LINE_LENGTH){
    buff[pos++] = next;
  }
  buff[pos] = '\0';
  if (next == '\n'){
    return buff;
  }
  else{
    return NULL;
  }
}


// Helper functions


FILE * get_stream(char * file_name)
{
  //! Opens given file and returns a file stream after performing error checking
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
  int file_ind  = 0, c_option = -1, ok = 1;
  int n_option = 10;
  FILE * file;
  char * opts_to_find = "n:c:";
  //! Decode the command line arguments, get the number of lines/chars to print
  //! and the index of the first file argument
  file_ind = decode_options(opts_to_find, argc, argv, &c_option, &n_option);
  if (file_ind == 0){
    file = stdin;
    if (c_option > -1){
      head_chars(file, c_option);
    }
    else{
      head_lines(file, n_option);
    }
  }
  else{
    //! Loop through file args
    for (int i = file_ind; i < argc; i++){
      file = get_stream(argv[i]);
      if (file != NULL){
        //! Print a header if there are multiple files
        if (argc - 1 - file_ind > 0){
          printf("==> %s <==\n", argv[i]);
        }
        if (c_option > -1){
          head_chars(file, c_option);
        }
        else {
          head_lines(file, n_option);
        }
      }
      else{
        //! The specified file does not exist, raise the error flag
        ok = 0;
      }
    }
  }

  if (ok == 1){
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}
