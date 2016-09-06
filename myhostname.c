#include <getopt.h>
#include <stdio.h>
#include <netdb.h>
#include "support.h"
#include <sys/unistd.h>
#include <string.h>

#define _GNU_SOURCE

int gethostname();

/*
 * host() - Print the hostname of the machine on which this program is
 *          running, formatted a few different ways
 */
void host(void) {
  char hostname [256];
  if(0 != gethostname(hostname, sizeof hostname)){
    printf("Error getting hostname\n");
  }else{
    char temp [256];
    int i;
    for(i = 0; i < strlen(hostname); i++){
      temp[i] = tolower(hostname[i]);
    }
    temp[i] = '\0';
    printf("%s\n", temp);

    for(i = 0; i < strlen(hostname); i++){
      temp[i] = toupper(hostname[i]);
    }
    temp[i] = '\0';
    printf("%s\n", temp);
    
    printf("%s\n", hostname);

    int c, j;
    for (i = 0, j = strlen(hostname) - 1; i < j; i++, j--){
      c = hostname[i];
      hostname[i] = hostname[j];
      hostname[j] = c;
    }
    printf("%s\n", hostname);
  }
}

/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Display the hostname of the machine\n");
    printf("The name will be displayed four ways, in the following order, on "
           "four lines:\n");
    printf("  all lowercase\n");
    printf("  ALL UPPERCASE\n");
    printf("  mIxEd LoWeRaNdUpPeR\n");
    printf("  emantsoh (i.e., reversed)\n");
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

    /* no need to look at arguments before calling the code */
    host();
}
