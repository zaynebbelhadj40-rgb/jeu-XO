#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matches.h"
#include "players.h"

Match* find_match_by_id(Match *matches, int mcount, int id) {
    for (int i = 0; i < mcount; i++) {
        if (matches[i].id == id) {
            return &matches[i];
        }
    }
    return NULL;
}

int add_match(Match *matches, int *mcount, int p1, int p2) {
    if (*mcount >= MAX_MATCHES) {
        printf("Nombre maximum de matchs atteint!\n");
        return -1;
    }

    if (p1 == p2) {
        printf("Un joueur ne peut pas jouer contre lui-meme!\n");
        return -1;
    }

    int new_id = 1;
    for (int i = 0; i < *mcount; i++) {
        if (matches[i].id >= new_id) {
            new_id = matches[i].id + 1;
        }
    }

    Match *new_match = &matches[*mcount];
    new_match->id = new_id;
    new_match->player1_id = p1;
    new_match->player2_id = p2;
    new_match->result = 0;

    (*mcount)++;
    printf("Match cree (ID: %d)\n", new_id);

    return new_id;
}

int set_match_result(Match *matches, int mcount, int id, int result) {
    Match *match = find_match_by_id(matches, mcount, id);
    if (match == NULL) {
        printf("Match avec ID %d non trouve!\n", id);
        return -1;
    }

    if (result < 0 || result > 3) {
        printf("Resultat invalide! Doit etre entre 0 et 3\n");
        return -1;
    }

    match->result = result;
    printf("Resultat du match %d mis a jour: %d\n", id, result);

    return 0;
}

int remove_match_if_unplayed(Match *matches, int *mcount, int id) {
    Match *match = find_match_by_id(matches, *mcount, id);
    if (match == NULL) {
        printf("Match avec ID %d non trouve!\n", id);
        return -1;
    }

    if (match->result != 0) {
        printf("Impossible de supprimer un match deje joue!\n");
        return -1;
    }

    int pos = -1;
    for (int i = 0; i < *mcount; i++) {
        if (matches[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) return -1;

    for (int i = pos; i < *mcount - 1; i++) {
        matches[i] = matches[i + 1];
    }

    (*mcount)--;
    printf("Match supprime!\n");

    return 0;
}

void print_matches(Match *matches, int mcount, Player *players, int pcount) {
    if (mcount == 0) {
        printf("Aucun match enregistre.\n");
        return;
    }

    printf("\n=== LISTE DES MATCHS ===\n");
    printf("ID | Joueur 1          | Joueur 2          | Statut\n");
    printf("---|-------------------|-------------------|----------------\n");

    for (int i = 0; i < mcount; i++) {
        Player *p1 = find_player_by_id(players, pcount, matches[i].player1_id);
        Player *p2 = find_player_by_id(players, pcount, matches[i].player2_id);

        char *status;
        switch (matches[i].result) {
            case 0: status = "Non joue"; break;
            case 1: status = "Joueur 1 gagne"; break;
            case 2: status = "Joueur 2 gagne"; break;
            case 3: status = "Match nul"; break;
            default: status = "Inconnu"; break;
        }

        printf("%-2d | %-17s | %-17s | %s\n",
               matches[i].id,
               p1 ? p1->name : "Inconnu",
               p2 ? p2->name : "Inconnu",
               status);
    }
    printf("\n");
}
