#ifndef GAME_H
#define GAME_H

#define N 3
#define K 3

#include "players.h"
#include "matches.h"

char** alloc_move_history(int max_moves);
void free_move_history(char **hist, int max_moves);
void init_board(char board[N][N]);
void print_board(char board[N][N]);
int make_move(char board[N][N], int row, int col, char symbol);
int check_victory(char board[N][N], char symbol);
int is_board_full(char board[N][N]);
int play_match_interactive(Match *m, Player *p1, Player *p2);

#endif
