#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

typedef struct Ship {
  int x;
  int y;
  int length;
  bool horizontal;
  bool initialized;
} Ship;

void display(Ship *ships, bool guesses[10][10], bool masked, int last_guess[2]);
int check_for_ship(Ship *ships, int x, int y);

#endif
