#include <display.h>
#include <stdio.h>
#include <util.h>

int check_for_ship(Ship *ships, int x, int y) {
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

void display(Ship *ships, bool guesses[10][10], bool masked,
             int last_guess[2]) {
  grey_text();
  printf("  A B C D E F G H I J\n");
  reset_text();
  for (int i = 0; i < 10; i++) {
    grey_text();
    printf("%d ", i);
    reset_text();
    for (int j = 0; j < 10; j++) {
      if (i == last_guess[0] && j == last_guess[1]) {
        invert_text();
      }
      if (masked) {
        int l = check_for_ship(ships, i, j);
        if (guesses[i][j]) {
          if (l != -1) {
            red_text();
            printf("X");
            reset_text();
          } else {
            printf("O");
          }
        } else {
          printf(".");
        }
      } else {
        int l = check_for_ship(ships, i, j);
        if (l != -1) {
          if (guesses[i][j]) {
            red_text();
            printf("X");
            reset_text();
          } else {
            blue_text();
            printf("%d", l + 1);
            reset_text();
          }
        } else {
          if (guesses[i][j]) {
            printf("O");
          } else {
            printf(".");
          }
        }
      }
      if (i == last_guess[0] && j == last_guess[1]) {
        reset_text();
      }
      printf(" ");
    }
    printf("\n");
  }
}
