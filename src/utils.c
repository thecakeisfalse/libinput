#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libinput.h"

char * replace(char * string, char * old, char * now) {
    int i = 0;
    int result_string_length = 0;
    int old_count = 0;
    int old_length = 0;
    int now_length = 0;
    char * result;

    for (i = 0; string[i] != '\0'; i++) {
        if (strstr(&string[i], old) == &string[i]) {
            old_count++;
            i = i + (old_length-1);
        }
    }

    result_string_length = (i + old_count * (now_length - old_length) + 1);
    i = 0;

    result = (char *)calloc(sizeof(char), result_string_length);
    if (result == NULL) {
        printf("Fatal: failed to allocte %u bytes.\n", result_string_length);
        exit(1);
    }

    while (*string) {
        if (strstr(string, old) == string) {
            strcpy(&result[i], now);
            i += now_length;
            string += old_length;
        } else {
            result[i++] = *string++;
        }
    }
    result[i] = '\0';

    return result;
}

char * sdup(char * string) {
    int length = strlen(string) + 1;
    char * result = (char *)calloc(sizeof(char), length);
    memcpy(result, string, length);
    return result;
}
