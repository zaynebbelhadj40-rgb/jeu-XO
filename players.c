#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "players.h"
#include "matches.h"

Player* find_player_by_id(Player *players, int pcount, int id) {
    for (int i = 0; i < pcount; i++) {
        if (players[i].id == id) {
            return &players[i];
        }
    }
    return NULL;
}

int player_exists_by_name(Player *players, int pcount, const char *name) {
    for (int i = 0; i < pcount; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_player(Player *players, int *pcount, const char *name) {
    if (*pcount >= MAX_PLAYERS) {
        printf("Nombre maximum de joueurs atteint!\n");
        return -1;
    }

    if (strlen(name) == 0) {
        printf("Le nom ne peut pas etre vide!\n");
        return -1;
    }

    if (player_exists_by_name(players, *pcount, name)) {
        printf("Un joueur avec ce nom existe deja!\n");
        return -1;
    }

    int new_id = 1;
    for (int i = 0; i < *pcount; i++) {
        if (players[i].id >= new_id) {
            new_id = players[i].id + 1;
        }
    }

    Player *new_player = &players[*pcount];
    new_player->id = new_id;
    strncpy(new_player->name, name, MAX_NAME_LEN);
    new_player->name[MAX_NAME_LEN] = '\0';
    new_player->wins = 0;
    new_player->losses = 0;
    new_player->draws = 0;

    (*pcount)++;
    printf("Joueur ajoute (ID: %d, Nom: %s)\n", new_id, name);

    return new_id;
}

int remove_player(Player *players, int *pcount, Match *matches, int mcount, int id) {
    Player *player = find_player_by_id(players, *pcount, id);
    if (player == NULL) {
        printf("Joueur avec ID %d non trouve!\n", id);
        return -1;
    }

    for (int i = 0; i < mcount; i++) {
        if ((matches[i].player1_id == id || matches[i].player2_id == id) && matches[i].result != 0) {
            printf("Impossible de supprimer: joueur a deja joue des matchs!\n");
            return -1;
        }
    }

    int pos = -1;
    for (int i = 0; i < *pcount; i++) {
        if (players[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) return -1;

    for (int i = pos; i < *pcount - 1; i++) {
        players[i] = players[i + 1];
    }

    (*pcount)--;
    printf("Joueur supprime!\n");

    return 0;
}

void print_players(Player *players, int pcount) {
    if (pcount == 0) {
        printf("Aucun joueur enregistre.\n");
        return;
    }

    printf("\n=== LISTE DES JOUEURS ===\n");
    printf("ID  | Nom                 | Victoires | Defaites | Nuls\n");
    printf("----|---------------------|-----------|----------|------\n");

    for (int i = 0; i < pcount; i++) {
        printf("%-3d | %-20s | %-9d | %-8d | %-4d\n",
               players[i].id,
               players[i].name,
               players[i].wins,
               players[i].losses,
               players[i].draws);
    }
    printf("\n");
}
