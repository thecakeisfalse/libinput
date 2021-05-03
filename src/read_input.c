#include "input.h"
#include <stdlib.h>
#include <string.h>

static char * line;
static int size = 0;
static int real_size = 2;

char * read_input(char * prompt) {
    char ch;
    int do_highlight = highlight_enabled();
    char * temp;

    printf("%s", prompt);

    if (line) {
        free(line);
    }

    line = (char *)calloc(sizeof(char), real_size);

    while ((ch = getch())) {
        if (ch == '\n') {
            putchar(ch);
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
            memset(line+size, 0, real_size-size);
        }

        line[size++] = ch;

        if (do_highlight) {
            temp = highlight(line);
        } else {
            temp = sdup(line);
        }


        printf("\r%s%s", prompt, temp);
        free(temp);
    }

    return line;
}
