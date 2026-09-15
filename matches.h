#ifndef MATCHES_H
#define MATCHES_H

#define MAX_MATCHES 1000

typedef struct Player Player;

typedef struct Match {
    int id;
    int player1_id;
    int player2_id;
    int result;
} Match;

Match* find_match_by_id(Match *matches, int mcount, int id);
int add_match(Match *matches, int *mcount, int p1, int p2);
int set_match_result(Match *matches, int mcount, int id, int result);
void print_matches(Match *matches, int mcount, Player *players, int pcount);
int remove_match_if_unplayed(Match *matches, int *mcount, int id);

#endif
