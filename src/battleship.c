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

bool check_ships_collision(ship ships[], ship new_ship) {
  for (int i = 0; i < 5; i++) {
    if (ships[i].initialized) {
      if (new_ship.horizontal) {
        for (int j = 0; j < new_ship.length; j++) {
          if (ships[i].x == new_ship.x + j && ships[i].y == new_ship.y) {
            return true;
          }
        }
      } else {
        for (int j = 0; j < new_ship.length; j++) {
          if (ships[i].x == new_ship.x && ships[i].y == new_ship.y + j) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void random_position(ship *new_ship) {
  new_ship->horizontal = rand() % 2;

  if (new_ship->horizontal) {
    new_ship->x = rand() % (10 - new_ship->length);
    new_ship->y = rand() % 10;
  } else {
    new_ship->x = rand() % 10;
    new_ship->y = rand() % (10 - new_ship->length);
  }
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

void guess(bool guesses[10][10], int x, int y, int *last_guess) {
  guesses[x][y] = true;
  last_guess[0] = x;
  last_guess[1] = y;
}

void random_guess(bool guesses[10][10], int *last_guess) {
  int x = rand() % 10;
  int y = rand() % 10;
  while (guesses[x][y]) {
    x = rand() % 10;
    y = rand() % 10;
  }
  guess(guesses, x, y, last_guess);
}

int get_num_hits(ship *ships, bool guesses[10][10]) {
  int hits = 0;
  for (int i = 0; i < 5; i++) {
    if (ships[i].initialized) {
      if (ships[i].horizontal) {
        for (int j = 0; j < ships[i].length; j++) {
          if (guesses[ships[i].x + j][ships[i].y]) {
            hits++;
          }
        }
      } else {
        for (int j = 0; j < ships[i].length; j++) {
          if (guesses[ships[i].x][ships[i].y + j]) {
            hits++;
          }
        }
      }
    }
  }
  return hits;
}

void display_score(board game_board) {
  int player_1_score =
      get_num_hits(game_board.player_1_ships, game_board.player_2_guesses);
  int player_2_score =
      get_num_hits(game_board.player_2_ships, game_board.player_1_guesses);

  printf("%d/%d\n\n", player_2_score, player_1_score);
}

void display_board(board game_board, bool masked) {
  display_score(game_board);

  display(game_board.player_2_ships, game_board.player_1_guesses, masked,
          game_board.player_1_last_guess);
  printf("\n");
  display(game_board.player_1_ships, game_board.player_2_guesses, false,
          game_board.player_2_last_guess);
}

int main_game(game *game) {
}
