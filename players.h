#ifndef PLAYERS_H
#define PLAYERS_H

#define MAX_PLAYERS 100
#define MAX_NAME_LEN 49

typedef struct Player {
    int id;
    char name[50];
    int wins;
    int losses;
    int draws;
} Player;

typedef struct Match Match;

Player* find_player_by_id(Player *players, int pcount, int id);
int add_player(Player *players, int *pcount, const char *name);
int remove_player(Player *players, int *pcount, Match *matches, int mcount, int id);
void print_players(Player *players, int pcount);
int player_exists_by_name(Player *players, int pcount, const char *name);

#endif
