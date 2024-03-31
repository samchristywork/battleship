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

#endif
