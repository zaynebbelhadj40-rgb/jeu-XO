#ifndef FILEIO_H
#define FILEIO_H

#include "players.h"
#include "matches.h"

int load_tournament(const char *filename, Player *players, int *pcount, Match *matches, int *mcount);
int save_tournament(const char *filename, Player *players, int pcount, Match *matches, int mcount);

#endif
