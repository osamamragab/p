#include <stdio.h>
#include <stdlib.h>

#define PROGNAME "pico"

int main(int argc, char *argv[]) {
  FILE *input;
  if (argc > 1) {
    input = fopen(argv[1], "r");
    if (!input) {
      fprintf(stderr, PROGNAME ": unable to read file \"%s\"\n", argv[1]);
      exit(1);
    }
  } else {
    input = stdin;
  }

  return 0;
}
