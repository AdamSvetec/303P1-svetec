#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * wc_file() - count characters, words, and lines
 */
void wc_file(char *filename) {
  if(filename == NULL)
    exit(1);

  int c;
  int char_count = 0;
  int word_count = 0;
  int line_count = 0;
  int whitespace_flag = 1;
  FILE * fp;
  fp = fopen(filename, "r");
  if(fp == NULL)
    exit(1);
  do{
    c = getc(fp);
    if((c == ' ' || c == '\t') && whitespace_flag == 0){
      word_count++;
      whitespace_flag = 1;
    }else if(c == '\n'){
      line_count++;
      if(whitespace_flag == 0){
	word_count++;
      }
      whitespace_flag = 1;
    }else if(c != ' ' && c != '\t' && c != '\n'){
      whitespace_flag = 0;
    }
    char_count++;
  }while(c != EOF);
  char_count--; //for eof
  printf("%d %d %d %s\n",line_count, word_count, char_count, filename);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print newline, word, and byte counts for FILE\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;

    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage. */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* error if we don't have a file, else call wc_file */
    if (argc != 2) {
        printf("Error: no file given\n");
        exit(1);
    }
    wc_file(argv[1]);
}
