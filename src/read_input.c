#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libinput.h>

char * read_input(char * prompt) {
    int i = 0;
    int current_string_index = 0;
    int real_string_size = 1;
    int string_size = 2;

    char * result = NULL;
    char chr = 0;

    result = (char *)calloc(sizeof(char), string_size);
    if (result == NULL) {
        printf("Fatal: failed to allocte %u bytes.\n", string_size);
        exit(1);
    }

    printf("%s", prompt);

    while ((chr = getch())) {
        if (chr == '\n') {
            putchar(chr);
            break;
        }

        if (chr == 127) {
            if (real_string_size > 1) {
                printf("\b \b");
                result[real_string_size-1] = '\0';

                real_string_size--;
                current_string_index--;
            }
            continue;
        }

        if (chr == ESCAPE) {
#ifndef _WIN32
            getch();
#endif
            chr = getch();

            if (chr == ARROW_UP) {

            } else if (chr == ARROW_DOWN) {

            } else if (chr == ARROW_LEFT) {
                if (current_string_index < real_string_size) {
                    printf("\033[C");
                    current_string_index++;
                }
            } else if (chr == ARROW_RIGHT) {
                if (current_string_index > 0) {
                    printf("\033[D");
                    current_string_index--;
                }
            }

            continue;
        }

        if (real_string_size >= string_size) {
            string_size <<= 1;

            result = (char *)realloc(result, string_size);
            if (result == NULL) {
                printf("Fatal: failed to allocte %u bytes.\n", string_size);
                exit(1);
            }

            memset(result+real_string_size, 0, string_size-real_string_size);
        }

        for (i = real_string_size-1; i >= current_string_index; i--) {
            result[i+1] = result[i];
        }
        result[current_string_index] = chr;
        result[real_string_size] = '\0';

        current_string_index++;
        real_string_size++;

        printf("\r%s%s", prompt, result);

        for (i = real_string_size-1; i > current_string_index; i--) {
            printf("\033[D");
        }
    }

    return result;
}
