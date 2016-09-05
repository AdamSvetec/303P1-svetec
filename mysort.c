#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "support.h"

/* Function used to compare lines */ 
int compare_function(const void * a, const void * b){
  return strcmp(*(char**)a, *(char**)b);
}

void print_lines(char ** lines, int length){
  for(int i = 0; i < length; i++){
    fprintf(stderr,"%s",lines[i]);
  }
}

/* Removes identical strings from array */
void make_unique(char ** lines, int *length){
  for(int pointer = 1; pointer < *length; pointer++){
    if(strcmp(lines[pointer], lines[pointer-1]) == 0){
      free(lines[pointer-1]);
      for(int shifter = pointer; shifter < *length; shifter++){
	lines[shifter-1] = lines[shifter];
      }
      (*length)--;
      pointer--;
    }
  }
}

/* Reverses lines */
void reverse_arr(char ** lines, int length){
  char * temp;
  int start = 0;
  int end = length - 1;
  while(start < end){
    temp = lines[start];
    lines[start] = lines[end];
    lines[end] = temp;
    start++;
    end--;
  }
}

/*
 * sort_file() - read a file, sort its lines, and output them.  reverse and
 *               unique parameters are booleans to affect how the lines are
 *               sorted, and which lines are output.
 */
void sort_file(char *filename, int unique, int reverse) {
  char ** lines;
  lines = malloc(1000000 * sizeof(char*));

  FILE * fp;
  fp = fopen(filename, "r");
  if(fp == NULL)
    exit(1);

  int line_num = 0;
  lines[line_num] = (char *)malloc(1024*sizeof(char));
  while(fgets(lines[line_num], 1024, fp) != NULL){
    line_num++;
    lines[line_num] = (char *)malloc(1024*sizeof(char));
  }
  fclose(fp);
  
  qsort(lines, line_num, sizeof(char*), compare_function);

  if(unique)
    make_unique(lines, &line_num);

  if(reverse)
    reverse_arr(lines,line_num);
  
  int pointer = 0;
  while(pointer < line_num){
    printf("%s", lines[pointer]);
    free(lines[pointer]);
    pointer++;
  }
  free(lines);
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s [OPTIONS] FILE\n", progname);
    printf("Sort the lines of FILE and print them to STDOUT\n");
    printf("  -r    sort in reverse\n");
    printf("  -u    only print unique lines\n");
}

/*
 * main() - The main routine parses arguments and dispatches to the
 *          task-specific code.
 */
int main(int argc, char **argv) {
    /* for getopt */
    long opt;
    int reverse = 0;
    int unique = 0;

    /* ensure the student name is filled out */
    check_student(argv[0]);

    /* parse the command-line options.  They are 'r' for reversing the */
    /* output, and 'u' for only printing unique strings.  'h' is also */
    /* supported. */
    while ((opt = getopt(argc, argv, "hru")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
	  case 'r': reverse = 1; break;
	  case 'u': unique = 1; break;
	}
    }

    sort_file(argv[optind], unique, reverse);
}
