#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include <display.h>

typedef struct board {
  bool player_1_guesses[10][10];
  bool player_2_guesses[10][10];
  ship player_1_ships[5];
  ship player_2_ships[5];
  int player_1_last_guess[2];
  int player_2_last_guess[2];
} board;

typedef struct game {
  board game_board;
} game;

int lengths[5] = {2, 3, 3, 4, 5};

int main_game(game *game) {
}
