#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

/*
 * grep_file() - display all lines of filename that contain searchstr
 */
void grep_file(char *filename, char *searchstr) {
  if(searchstr == NULL){
    printf("Error: search string needed\n");
    exit(1);
  }

  FILE * fp;
  if(filename == NULL){
    fp = stdin;
  }else{
    fp = fopen(filename, "r");
  }
  if(fp == NULL){
    printf("Error: File could not be opened\n");
    exit(1);
  }
  
  char line [1024];
  while(fgets(line, 1024, fp) != NULL){
    if(strstr(line, searchstr) != NULL){
      printf("%s", line);
    }
  }
  fclose(fp);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s STR FILE\n", progname);
    printf("Print to STDOUT the lines of FILE that contain STR\n");
    printf("With no FILE, read standard input\n");
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

    grep_file(argv[2], argv[1]);
}
