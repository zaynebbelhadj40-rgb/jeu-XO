#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "players.h"
#include "matches.h"

int load_tournament(const char *filename, Player *players, int *pcount, Match *matches, int *mcount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fichier %s non trouve.\n", filename);
        return -1;
    }

    char line[4096];
    *pcount = 0;
    *mcount = 0;

    if (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "PLAYERS", 7) == 0) {
            char *token = strtok(line + 7, " ");
            while (token != NULL && *pcount < MAX_PLAYERS) {
                Player p;
                if (sscanf(token, "%d;%49[^;];%d;%d;%d",
                           &p.id, p.name, &p.wins, &p.losses, &p.draws) == 5) {
                    players[*pcount] = p;
                    (*pcount)++;
                }
                token = strtok(NULL, " ");
            }
        }
    }

    if (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MATCHES", 7) == 0) {
            char *token = strtok(line + 7, " ");
            while (token != NULL && *mcount < MAX_MATCHES) {
                Match m;
                if (sscanf(token, "%d;%d;%d;%d",
                           &m.id, &m.player1_id, &m.player2_id, &m.result) == 4) {
                    matches[*mcount] = m;
                    (*mcount)++;
                }
                token = strtok(NULL, " ");
            }
        }
    }

    fclose(file);
    printf("Tournoi charge: %d joueurs, %d matchs\n", *pcount, *mcount);
    return 0;
}

int save_tournament(const char *filename, Player *players, int pcount, Match *matches, int mcount) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur creation fichier %s\n", filename);
        return -1;
    }

    fprintf(file, "PLAYERS");
    for (int i = 0; i < pcount; i++) {
        fprintf(file, " %d;%s;%d;%d;%d",
                players[i].id, players[i].name,players[i].wins, players[i].losses, players[i].draws);
    }
    fprintf(file, "\nMATCHES");
    for (int i = 0; i < mcount; i++) {
        fprintf(file, " %d;%d;%d;%d",matches[i].id, matches[i].player1_id,matches[i].player2_id, matches[i].result);
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Tournoi sauvegarde dans %s\n", filename);
    return 0;
}
