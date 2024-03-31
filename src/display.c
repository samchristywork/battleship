#include <display.h>
#include <stdio.h>
#include <util.h>

int check_for_ship(ship *ships, int x, int y) {
  for (int i = 0; i < 5; i++) {
    if (ships[i].initialized) {
      if (ships[i].horizontal) {
        for (int j = 0; j < ships[i].length; j++) {
          if (ships[i].x + j == x && ships[i].y == y) {
            return i;
          }
        }
      } else {
        for (int j = 0; j < ships[i].length; j++) {
          if (ships[i].x == x && ships[i].y + j == y) {
            return i;
          }
        }
      }
    }
  }
  return -1;
}
