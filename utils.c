#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void clear_stdin_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n')
        s[len-1] = '\0';
}

int safe_read_int(const char *prompt, int *out, int min, int max) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            return -1;

        if (sscanf(buffer, "%d", &value) == 1) {
            if (value >= min && value <= max) {
                *out = value;
                return 0;
            } else {
                printf("Valeur doit etre entre %d et %d\n", min, max);
            }
        } else {
            printf("Entree invalide. Entrez un nombre.\n");
        }
    }
}
