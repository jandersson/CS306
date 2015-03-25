//! A head copy-cat
/*!
  This program attempts to implement the functionality of the GNU head program
*/

#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_LINE_LENGTH 100
#define FILE_BUFFER_SIZE 512
//Initial size for line buffer
#define INIT_BUFF_SIZE 50
//Minimum number of bytes by which line buffer will be expanded
#define INC_BUFF_SIZE 10
// Function Prototypes

void print_args(int argc, char * argv[]);
void head_lines(int fd, int lines);
void head_chars(int fd, int chars);
char * get_next_line(int fd);
int get_char(int fd);
int decode_options(char * opts_to_find, int argc, char * argv[], int * c_option,int * n_option);
int get_stream(char * file_name);
void print_usage(char * argv[]);

// Display related functions

void print_usage(char * argv[]){
  printf("Usage: %s [-n # | -c #] {FILE}\n", argv[0]);
  return;
}

void print_args(int argc, char * argv[]){
  printf("Number of options: %d\n", argc-1);
  for (int i = 1; i < argc; i++){
    printf("Argument %d: %s\n", i, argv[i]);
  }
  return;
}


// Required functions

int get_char(int fd){
  char buffer;
  static int buffer_position = 0;
  if(read(fd, &buffer, 1) < 1)
    return EOF;
  else
    return buffer;
}

void head_chars(int fd, int chars){
  int chars_iter = 0;
  int c;
    while ((c = get_char(fd)) != -1 && chars_iter < chars){
      printf("%c",c);
      chars_iter++;
    }
  close(fd);
  return;
}

void head_lines(int fd, int lines){
  for (int i = 0; i < lines; i++){
    char * line = get_next_line(fd);
    if (line != NULL){
      printf("%s\n", line);
    }
    else{
      break;
    }
  }
  return;
}


char * get_next_line(int fd){
  static char buff[MAX_LINE_LENGTH+1];
  int pos = 0, next_character = 0;
  while ((next_character = get_char(fd)) != EOF && next_character != '\n'){
    buff[pos++] = next_character;
  }
  buff[pos] = '\0';
  if (next_character == EOF && (errno || pos == 0 )){
    return NULL;
  }
  else{
    return buff;
  }
}


// Helper functions


int get_stream(char * file_name)
{
  //! Opens given file and returns a file stream after performing error checking
  int fd = -1;
  if ((fd = open(file_name, O_RDONLY)) == -1){
    fprintf(stderr, "myhead: cannot open '%s' for reading: No such file or directory\n", file_name);
  }
  else{
    int fd = open(file_name, O_RDONLY);
  }
  return fd;
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
  int file_ind  = 0, c_option = -1;
  int n_option = 10;
  int file;
  char * opts_to_find = "n:c:";
  //! Decode the command line arguments, get the number of lines/chars to print
  //! and the index of the first file argument
  file_ind = decode_options(opts_to_find, argc, argv, &c_option, &n_option);
  if (file_ind == 0){
    file = 0; //stdin is tied to file descriptor 0
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
      if (!errno){
        //! Print a header if there are multiple files
        if (argc - 1 - file_ind > 0){
          if(i > file_ind) putchar('\n');
          printf("==> %s <==\n", argv[i]);
        }
        if (c_option > -1){
          head_chars(file, c_option);
        }
        else {
          head_lines(file, n_option);
        }
      }
    }
  }

  if (errno){
    exit(EXIT_FAILURE);
  }
  else {
    exit(EXIT_SUCCESS);
  }
}
