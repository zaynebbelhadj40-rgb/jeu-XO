#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "players.h"
#include "matches.h"

char** alloc_move_history(int max_moves) {
    char **history = malloc(max_moves * sizeof(char*));
    if (history == NULL) return NULL;

    for (int i = 0; i < max_moves; i++) {
        history[i] = malloc(10 * sizeof(char));
        if (history[i] == NULL) {
            for (int j = 0; j < i; j++) free(history[j]);
            free(history);
            return NULL;
        }
        history[i][0] = '\0';
    }
    return history;
}

void free_move_history(char **hist, int max_moves) {
    if (hist == NULL) return;
    for (int i = 0; i < max_moves; i++) free(hist[i]);
    free(hist);
}

void init_board(char board[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';
}

void print_board(char board[N][N]) {
    printf("\n  ");
    for (int j = 0; j < N; j++) printf(" %d  ", j + 1);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");

        if (i < N - 1) {
            printf("  ");
            for (int j = 0; j < N; j++) {
                printf("---");
                if (j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int make_move(char board[N][N], int row, int col, char symbol) {
    if (row < 0 || row >= N || col < 0 || col >= N) return 0;
    if (board[row][col] != ' ') return 0;
    board[row][col] = symbol;
    return 1;
}

int check_victory(char board[N][N], char symbol) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == symbol) {
                if (j <= N-K) {
                    int win = 1;
                    for (int k = 0; k < K; k++)
                        if (board[i][j+k] != symbol) win = 0;
                    if (win) return 1;
                }
                if (i <= N-K) {
                    int win = 1;
                    for (int k = 0; k < K; k++)
                        if (board[i+k][j] != symbol) win = 0;
                    if (win) return 1;
                }
                if (i <= N-K && j <= N-K) {
                    int win = 1;
                    for (int k = 0; k < K; k++)
                        if (board[i+k][j+k] != symbol) win = 0;
                    if (win) return 1;
                }
                if (i <= N-K && j >= K-1) {
                    int win = 1;
                    for (int k = 0; k < K; k++)
                        if (board[i+k][j-k] != symbol) win = 0;
                    if (win) return 1;
                }
            }
        }
    }
    return 0;
}

int is_board_full(char board[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

int play_match_interactive(Match *m, Player *p1, Player *p2) {
    char board[N][N];
    init_board(board);

    printf("\n=== MATCH %d: %s (X) vs %s (O) ===\n", m->id, p1->name, p2->name);

    char current_symbol = 'X';
    Player *current_player = p1;

    while (1) {
        print_board(board);
        printf("Tour de %s (%c)\n", current_player->name, current_symbol);

        int row, col;
        printf("Ligne (1-3): "); scanf("%d", &row);
        printf("Colonne (1-3): "); scanf("%d", &col);

        if (!make_move(board, row-1, col-1, current_symbol)) {
            printf("Case invalide!\n");
            continue;
        }

        if (check_victory(board, current_symbol)) {
            print_board(board);
            printf("%s gagne!\n", current_player->name);

            if (current_player == p1) {
                m->result = 1;
                p1->wins++; p2->losses++;
            } else {
                m->result = 2;
                p2->wins++; p1->losses++;
            }
            break;
        }

        if (is_board_full(board)) {
            print_board(board);
            printf("Match nul!\n");
            m->result = 3;
            p1->draws++; p2->draws++;
            break;
        }

        current_symbol = (current_symbol == 'X') ? 'O' : 'X';
        current_player = (current_player == p1) ? p2 : p1;
    }

    return m->result;
}
