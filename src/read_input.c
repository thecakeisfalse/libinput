#include "input.h"
#include <stdlib.h>

static char * line;
static int size = 0;
static int real_size = 2;

char * read_input(char * prompt) {
    char ch;

    printf("%s", prompt);

    if (line) {
        free(line);
    }

    line = (char *)calloc(sizeof(char), real_size);

    while ((ch = getch())) {
        putchar(ch);

        if (ch == '\n') {
            line[size] = 0;
            break;
        }

        if (ch == 127) {
            if (size > 0) {
                printf("\b \b");
                line[size] = 0;
                size--;
            }
            continue;
        }

        if (size >= real_size) {
            real_size *= 2;
            line = (char *)realloc(line, sizeof(char) * real_size);
        }

        line[size++] = ch;
    }

    return line;
}
