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

void init_board(board *game_board) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      game_board->player_1_guesses[i][j] = false;
      game_board->player_2_guesses[i][j] = false;
    }
  }

  game_board->player_1_last_guess[0] = -1;
  game_board->player_1_last_guess[1] = -1;
  game_board->player_2_last_guess[0] = -1;
  game_board->player_2_last_guess[1] = -1;
}

void init_ships(board *game_board) {
  for (int i = 0; i < 5; i++) {
    game_board->player_1_ships[i].initialized = false;
    game_board->player_2_ships[i].initialized = false;
  }

  for (int i = 0; i < 5; i++) {
    ship new_ship;
    new_ship.length = lengths[i];
    random_position(&new_ship);
    while (check_ships_collision(game_board->player_1_ships, new_ship)) {
      random_position(&new_ship);
    }
    game_board->player_1_ships[i] = new_ship;
  }

  for (int i = 0; i < 5; i++) {
    ship new_ship;
    new_ship.length = lengths[i];
    random_position(&new_ship);
    while (check_ships_collision(game_board->player_2_ships, new_ship)) {
      random_position(&new_ship);
    }
    game_board->player_2_ships[i] = new_ship;
  }
}

int main_game(game *game) {
}
