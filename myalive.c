#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "support.h"
#include <unistd.h>

volatile int sig_flag = 0;
void sighandler(int);

/*
 * alive() - install some signal handlers, set an alarm, and wait...
 */
void alive(void) {
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
  signal(SIGINT, sighandler);
  signal(SIGALRM, sighandler);
  alarm(10);
  while(1){
    switch (sig_flag){
      case SIGINT:
	fprintf(stderr,"\nno\n");
	sig_flag = 0;
	signal(SIGINT, sighandler);
	break;
      case SIGALRM:
	gettimeofday(&end, NULL);
	long elapsed = end.tv_sec-start.tv_sec;
	fprintf(stderr, "Ran for %ld seconds\n", elapsed);
	exit(1);
      }
  }
}

void sighandler(int signum){
  sig_flag = signum;
}


/*
 * help() - Print a help message.
 */
void help(char *progname) {
    printf("Usage: %s\n", progname);
    printf("Swallow SIGINT, exit on SIGALARM\n");
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
    alive();
}
