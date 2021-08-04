#include "input.h"
#include <stdlib.h>
#include <string.h>

static char * line;
static int line_index = 0;
static int line_size = 0;
static int real_line_size = 2;

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

    line = (char *)calloc(sizeof(char), real_line_size);

    while ((ch = getch())) {
        if (ch == '\n') {
            putchar(ch);
            line[line_size] = 0;
            break;
        }

        if (ch == 127) {
            if (line_size > 0) {
                printf("\b \b");
                line[line_size] = 0;
                line_size--;
            }
            continue;
        }

        if (ch == 27) {
            getch();
            ch = getch();
            if (ch == 'A') {
                item = previous_history();
                if (item != NULL) {
                    for (i = 0; i < line_size; i++) {
                        printf("\b \b");
                    }
                    printf("\r%s%s", prompt, item);
                    line_size = strlen(item);
                    if (line_size > real_line_size) {
                        line = (char *)realloc(line, sizeof(char) * line_size);
                    }
                    strcpy(line, item);
                    line_index = line_size;
                }
            } else if (ch == 'B') {
                item = next_history();
                if (item != NULL) {
                    for (i = 0; i < line_size; i++) {
                        printf("\b \b");
                    }
                    printf("\r%s%s", prompt, item);
                    line_size = strlen(item);
                    if (line_size > real_line_size) {
                        line = (char *)realloc(line, sizeof(char) * line_size);
                    }
                    strcpy(line, item);
                    line_index = line_size;
                }
            } else if (ch == 'C') {
                if (line_index < line_size) {
                    printf("\033[C");
                    line_index++;
                }
            } else if (ch == 'D') {
                if (line_index > 0) {
                    printf("\033[D");
                    line_index--;
                }
            }
            continue;
        }

        if (line_size >= real_line_size) {
            real_line_size = line_size * 2;
            line = (char *)realloc(line, sizeof(char) * real_line_size);
            memset(line+line_size, 0, real_line_size-line_size);
        }

        if (line_index == line_size) {
            line[line_index++] = ch;
            line_size++;
        } else {
            for (i = line_size-1; i >= line_index; i--) {
                line[i+1] = line[i];
            }
            line[line_index] = ch;

            line_index++;
            line_size++;
        }

        if (do_highlight) {
            result = highlight(line);
        } else {
            result = sdup(line);
        }

        printf("\r%s%s", prompt, result);
        free(result);

        for (i = line_size; i > line_index; i--) {
            printf("\033[D");
        }
    }

    return line;
}
