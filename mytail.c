#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/*
 * tail_file() - display the last numlines lines of a file or stdin
 */
void tail_file(char *filename, int numlines) {
  char ** buffer;
  buffer = malloc(numlines * sizeof(char*));
  for(int i = 0; i < numlines; i++){
    buffer[i] = (char *)malloc(1024*sizeof(char));
  }
  
  FILE * fp;
  fp = fopen(filename, "r");
  if(fp == NULL)
    exit(1);

  int line_num = 0;
  while(fgets(buffer[line_num % numlines], 1024, fp) != NULL){
    line_num++;    
  }
  fclose(fp);
  for(int j = 0; j < numlines; j++){
    printf("%s", buffer[(line_num+j)%numlines]);
    free(buffer[(line_num+j)%numlines]);
  }
  free(buffer);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [FILE]\n", progname);
    printf("Print the last 10 lines  of FILE to STDOUT\n");
    printf("With no FILE, read from STDIN\n");
    printf("  -nK    print the last K lines instead of the last 10\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int numlines = 10;
    /* run a student name check */
    check_student(argv[0]);

    /* parse the command-line options.  For this program, we only support  */
    /* the parameterless 'h' option, for getting help on program usage, */
    /* and the parametered 'n' option, for getting the number of lines. */
    while ((opt = getopt(argc, argv, "hn:")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	  case 'n': numlines = atoi(optarg); break;
	}
    }

    tail_file(optind < argc ? argv[optind] : NULL, numlines);
}
