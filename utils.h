#ifndef UTILS_H
#define UTILS_H

int safe_read_int(const char *prompt, int *out, int min, int max);
void clear_stdin_buffer(void);
void strip_newline(char *s);

#endif
