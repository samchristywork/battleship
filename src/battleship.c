#include <display.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>

void handle_sigint(int sig) {
  printf("\nInterrupt signal (%d) received. Exiting gracefully...\n", sig);
  normal_screen();
  exit(0);
}

typedef struct Board {
  bool player_1_guesses[10][10];
  bool player_2_guesses[10][10];
  Ship player_1_ships[5];
  Ship player_2_ships[5];
  int player_1_last_guess[2];
  int player_2_last_guess[2];
} Board;

enum Difficulty {
  AI_NONE = 0,
  AI_EASY = 1,
  AI_MEDIUM = 2,
  AI_HARD = 3,
};

int lengths[5] = {2, 3, 3, 4, 5};

void init_board(Board *game_board) {
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

bool check_ships_collision(Ship ships[], Ship new_ship) {
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

void random_position(Ship *new_ship) {
  new_ship->horizontal = rand() % 2;

  if (new_ship->horizontal) {
    new_ship->x = rand() % (10 - new_ship->length);
    new_ship->y = rand() % 10;
  } else {
    new_ship->x = rand() % 10;
    new_ship->y = rand() % (10 - new_ship->length);
  }
}

void init_ships(Board *game_board) {
  for (int i = 0; i < 5; i++) {
    game_board->player_1_ships[i].initialized = false;
    game_board->player_2_ships[i].initialized = false;
  }

  for (int i = 0; i < 5; i++) {
    Ship new_ship;
    new_ship.length = lengths[i];
    random_position(&new_ship);
    while (check_ships_collision(game_board->player_1_ships, new_ship)) {
      random_position(&new_ship);
    }
    game_board->player_1_ships[i] = new_ship;
  }

  for (int i = 0; i < 5; i++) {
    Ship new_ship;
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

void ai_guess(bool guesses[10][10], int *last_guess, Ship *ships) {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      if (guesses[x][y]) {
        if (check_for_ship(ships, x, y) != -1) {
          if (x > 0 && !guesses[x - 1][y]) {
            guess(guesses, x - 1, y, last_guess);
            return;
          }
          if (x < 9 && !guesses[x + 1][y]) {
            guess(guesses, x + 1, y, last_guess);
            return;
          }
          if (y > 0 && !guesses[x][y - 1]) {
            guess(guesses, x, y - 1, last_guess);
            return;
          }
          if (y < 9 && !guesses[x][y + 1]) {
            guess(guesses, x, y + 1, last_guess);
            return;
          }
        }
      }
    }
  }
  random_guess(guesses, last_guess);
}

void cheating_ai_guess(bool guesses[10][10], int *last_guess, Ship *ships) {
  int chance = rand() % 100;
  if (chance < 10) {
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        if (!guesses[x][y]) {
          if (check_for_ship(ships, x, y) != -1) {
            guess(guesses, x, y, last_guess);
            return;
          }
        }
      }
    }
  } else {
    ai_guess(guesses, last_guess, ships);
  }
}

int get_num_hits(Ship *ships, bool guesses[10][10]) {
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

void display_score(Board game_board) {
  int player_1_score =
      get_num_hits(game_board.player_1_ships, game_board.player_2_guesses);
  int player_2_score =
      get_num_hits(game_board.player_2_ships, game_board.player_1_guesses);

  printf("%d/%d\n\n", player_2_score, player_1_score);
}

void display_board(Board game_board, bool masked) {
  display_score(game_board);

  display(game_board.player_2_ships, game_board.player_1_guesses, masked,
          game_board.player_1_last_guess);
  printf("\n");
  display(game_board.player_1_ships, game_board.player_2_guesses, false,
          game_board.player_2_last_guess);
}

bool has_won(Ship *ships, bool guesses[10][10]) {
  if (get_num_hits(ships, guesses) == 17) {
    return true;
  }
  return false;
}

void ship_selection(Board *board) {
  for (int i = 0; i < 5; i++) {
    board->player_1_ships[i].initialized = false;
  }
  for (int i = 0; i < 5; i++) {
    reset_cursor();
    display_board(*board, true);
    printf("\nPlace ship of length %d\n", lengths[i]);
    printf("Enter coordinates (e.g. A0, B1, C2, etc.): ");
    char s[10];
    scanf("%s", s);
    int x = s[1] - '0';
    int y = s[0] - 'A';
    Ship new_ship = {0};
    new_ship.x = x;
    new_ship.y = y;
    new_ship.length = lengths[i];

    printf("Enter orientation (h for horizontal, v for vertical): ");
    char o[10];
    scanf("%s", o);
    if (o[0] == 'v') {
      new_ship.horizontal = true;
    } else {
      new_ship.horizontal = false;
    }

    if (check_ships_collision(board->player_1_ships, new_ship)) {
      i--;
      continue;
    }

    board->player_1_ships[i] = new_ship;
    board->player_1_ships[i].initialized = true;
  }
}

int main_game(Board *board, int difficulty) {
  int winner = -1;
  while (1) {
    int x, y;
    reset_cursor();
    printf("Difficulty: %d\n", difficulty);
    display_board(*board, true);
    printf("\nEnter coordinates to guess (q to quit, r for random guess): ");
    char s[10];
    scanf("%s", s);
    if (s[0] == 'q') {
      break;
    } else if (s[0] == 'r') {
      random_guess(board->player_1_guesses, board->player_1_last_guess);
    } else if (s[0] < 'A' || s[0] > 'J' || s[1] < '0' || s[1] > '9') {
      continue;
    } else {
      x = s[1] - '0';
      y = s[0] - 'A';
      guess(board->player_1_guesses, x, y, board->player_1_last_guess);
    }

    if (has_won(board->player_2_ships, board->player_1_guesses)) {
      winner = 1;
      break;
    }

    if (difficulty == AI_EASY) {
      random_guess(board->player_2_guesses, board->player_2_last_guess);
    } else if (difficulty == AI_MEDIUM) {
      ai_guess(board->player_2_guesses, board->player_2_last_guess,
               board->player_1_ships);
    } else if (difficulty == AI_HARD) {
      cheating_ai_guess(board->player_2_guesses, board->player_2_last_guess,
                        board->player_1_ships);
    }

    if (has_won(board->player_1_ships, board->player_2_guesses)) {
      winner = 2;
      break;
    }
  }

  return winner;
}

int main() {
  signal(SIGINT, handle_sigint);

  Board board;

  init_board(&board);
  init_ships(&board);

  alternate_screen();
  clear_screen();

  printf("Do you want to select ship positions? (y/n): ");
  if (getchar() == 'y') {
    clear_screen();
    ship_selection(&board);
  }

  printf("Select difficulty (1 for easy, 2 for medium, 3 for hard, 0 for no "
         "AI): ");
  int difficulty;
  scanf("%d", &difficulty);

  clear_screen();

  int winner = main_game(&board, difficulty);
  normal_screen();

  printf("Final board:\n\n");
  display_board(board, false);

  if (winner != -1) {
    printf("\nPlayer %d wins!\n", winner);
  } else {
    printf("\nGame ended in a draw!\n");
  }
}
