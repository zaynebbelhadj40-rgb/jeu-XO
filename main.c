#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"
#include "matches.h"
#include "game.h"
#include "fileio.h"
#include "utils.h"

Player players[MAX_PLAYERS];
Match matches[MAX_MATCHES];
int pcount = 0;
int mcount = 0;

void display_menu() {
    printf("\n=== GESTION DE TOURNOI DE MORPION ===\n");
    printf("1. Afficher tous les joueurs\n");
    printf("2. Ajouter un joueur\n");
    printf("3. Supprimer un joueur\n");
    printf("4. Afficher tous les matchs\n");
    printf("5. Creer un nouveau match\n");
    printf("6. Jouer un match\n");
    printf("7. Supprimer un match non joue\n");
    printf("8. Charger le tournoi depuis un fichier\n");
    printf("9. Sauvegarder le tournoi dans un fichier\n");
    printf("10. Quitter\n");
    printf("\nChoix: ");
}

int main() {
    printf("Bienvenue dans le gestionnaire de tournoi de morpion!\n");

    load_tournament("players_matches.txt", players, &pcount, matches, &mcount);

    int choice;

    do {
        display_menu();
        safe_read_int("", &choice, 1, 10);

        switch(choice) {
            case 1:
                print_players(players, pcount);
                break;
            case 2: {
                char name[50];
                printf("Nom du joueur: ");
                fgets(name, 50, stdin);
                strip_newline(name);
                add_player(players, &pcount, name);
                break;
            }
            case 3: {
                int id;
                safe_read_int("ID du joueur a supprimer: ", &id, 1, 1000);
                remove_player(players, &pcount, matches, mcount, id);
                break;
            }
            case 4:
                print_matches(matches, mcount, players, pcount);
                break;
            case 5: {
                int p1, p2;
                safe_read_int("ID joueur 1: ", &p1, 1, 1000);
                safe_read_int("ID joueur 2: ", &p2, 1, 1000);
                add_match(matches, &mcount, p1, p2);
                break;
            }
            case 6: {
                int match_id;
                safe_read_int("ID du match a jouer: ", &match_id, 1, 1000);
                Match *match = find_match_by_id(matches, mcount, match_id);
                if (match && match->result == 0) {
                    Player *p1 = find_player_by_id(players, pcount, match->player1_id);
                    Player *p2 = find_player_by_id(players, pcount, match->player2_id);
                    if (p1 && p2) {
                        play_match_interactive(match, p1, p2);
                    } else {
                        printf("Joueur non trouve!\n");
                    }
                } else {
                    printf("Match non trouve ou deja joue!\n");
                }
                break;
            }
            case 7: {
                int match_id;
                safe_read_int("ID du match a supprimer: ", &match_id, 1, 1000);
                remove_match_if_unplayed(matches, &mcount, match_id);
                break;
            }
            case 8:
                load_tournament("players_matches.txt", players, &pcount, matches, &mcount);
                break;
            case 9:
                save_tournament("players_matches.txt", players, pcount, matches, mcount);
                break;
            case 10:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
        clear_stdin_buffer();
    } while (choice != 10);

    return 0;
}
