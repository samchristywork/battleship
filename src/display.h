#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

typedef struct ship {
  int x;
  int y;
  int length;
  bool horizontal;
  bool initialized;
} ship;

void display(ship *ships, bool guesses[10][10], bool masked,
             int last_guess[2]);

#endif
