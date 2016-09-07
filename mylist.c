#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "support.h"

/* link struct */
struct link{
  int value;
  struct link * next;
};

/* global head */
struct link * head;

/* insert value into list (sorted) */
void insert_val(int value){
  if(head == NULL){
    head = (struct link*)malloc(sizeof(struct link));
    head->value = value;
  }else{
    struct link * pointer = head;
    struct link * new_link = (struct link*)malloc(sizeof(struct link));
    new_link->value = value;
    if(pointer->value >= value){
      head = new_link;
      new_link->next = pointer;
      return;
    }
    while(pointer->next != NULL && pointer->next->value <= value){
      pointer = pointer->next;
    }
    new_link->next = pointer->next;
    pointer->next = new_link;
  }
}

/* remove value from list */
void remove_val(int value){
  struct link * pointer = head;
  struct link * last_visited;
  if(pointer == NULL){
    return;
  }
  if(pointer->value == value){
    head = pointer->next;
    free(pointer);
    return;
  }
  last_visited = pointer;
  pointer = pointer->next;
  while(pointer != NULL){
    if(pointer->value == value){
      last_visited->next = pointer->next;
      free(pointer);
      return;
    }
    last_visited = pointer;
    pointer = pointer->next;
  }
}

/* print list */
void print(){
  if(head == NULL){
    return;
  }
  struct link * pointer = head;
  printf("%d", pointer->value);
  while(pointer->next != NULL){
    pointer = pointer->next;
    printf("-->%d",pointer->value);
  }
  printf("\n");
}

/* delete list */
void delete_list(){
  struct link * pointer = head;
  struct link * next;
  while(pointer != NULL){
    next = pointer->next;
    free(pointer);
    pointer = next;
  }
}

/* get value from command that was issued */
void get_command_val(char * input, int * value){
  int pointer = 2;
  char str_value [100];
  while(input[pointer] != EOF && input[pointer] != '\n'){
    str_value[pointer-2] = input[pointer];
    pointer++;
  }
  str_value[pointer-2] = '\0';
  (*value) = (int) strtol(str_value, NULL, 10); //Not really safe but...
}

/*
 * list_task() - read from stdin, determine the appropriate behavior, and
 *               perform it.
 */
void list_task(void) {
  char input [100];
  char command;
  int value;
  while(1){
    if(fgets(input, 100, stdin) == NULL){
      exit(1);
    }
    command = input[0];
    switch (command){
    case 'x':
      delete_list();
      exit(1);
    case 'p':
      print();
      break;
    case 'i':
      get_command_val(input, &value);
      insert_val(value);
      break;
    case 'r':
      get_command_val(input, &value);
      remove_val(value);
      break;
    default:
      printf("Command not recognized\n");
      break;
    }
  }
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Run an interactive list manipulation program\n");
    printf("Commands: [i]insert, [r]emove, [p]rint, e[x]it\n");
    printf("  (Commands require an integer argument)\n");
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

    /*
     * parse the command-line options.  For this program, we only support the
     * parameterless 'h' option, for getting help on program usage.
     */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
          case 'h': help(argv[0]); break;
        }
    }

    /* run the list program */
    list_task();
}
