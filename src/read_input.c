#include "input.h"
#include <stdlib.h>
#include <string.h>

static char * line;
static int index = 0;
static int size = 0;
static int real_size = 2;

char * read_input(char * prompt) {
    char ch;
    int do_highlight = highlight_enabled();
    char * result;
    char * item;
    int i;

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

        if (ch == 27) {
            getch();
            ch = getch();
            if (ch == 'A') {
                item = previous_history();
                if (item != NULL) {
                    for (i = 0; i < size; i++) {
                        printf("\b \b");
                    }
                    printf("\r%s%s", prompt, item);
                    size = strlen(item);
                    if (size > real_size) {
                        line = (char *)realloc(line, sizeof(char) * size);
                    }
                    strcpy(line, item);
                    index = size;
                }
            } else if (ch == 'B') {
                item = next_history();
                if (item != NULL) {
                    for (i = 0; i < size; i++) {
                        printf("\b \b");
                    }
                    printf("\r%s%s", prompt, item);
                    size = strlen(item);
                    if (size > real_size) {
                        line = (char *)realloc(line, sizeof(char) * size);
                    }
                    strcpy(line, item);
                    index = size;
                }
            } else if (ch == 'C') {
                if (index < size) {
                    printf("\033[C");
                    index++;
                }
            } else if (ch == 'D') {
                if (index > 0) {
                    printf("\033[D");
                    index--;
                }
            }
            continue;
        }

        if (size >= real_size) {
            real_size = size * 2;
            line = (char *)realloc(line, sizeof(char) * real_size);
            memset(line+size, 0, real_size-size);
        }

        if (index == size) {
            line[index++] = ch;
            size++;
        } else {
            for (i = size-1; i >= index; i--) {
                line[i+1] = line[i];
            }
            line[index] = ch;

            index++;
            size++;
        }

        if (do_highlight) {
            result = highlight(line);
        } else {
            result = sdup(line);
        }

        printf("\r%s%s", prompt, result);
        free(result);

        for (i = size; i > index; i--) {
            printf("\033[D");
        }
    }

    return line;
}
