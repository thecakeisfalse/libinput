#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * replace(char * string, char * old, char * now) {
    char * result;
    int i, count = 0;
    int nowlen = strlen(now);
    int oldlen = strlen(old);
    int newlength = 0;

    for (i = 0; string[i] != '\0'; i++) {
        if (strstr(&string[i], old) == &string[i]) {
            count++;
            i += oldlen-1;
        }
    }

    newlength = (i+count*(nowlen-oldlen)+1);
    result = (char *)calloc(sizeof(char), newlength);

    i = 0;

    while (*string) {
        if (strstr(string, old) == string) {
            strcpy(&result[i], now);
            i += nowlen;
            string += oldlen;
        } else {
            result[i++] = *string++;
        }
    }

    result[i] = '\0';

    return result;
}

char * sdup(char * string) {
    int length = strlen(string)+1;
    char * res = (char *)malloc(sizeof(char) * length);
    memcpy(res, string, length);
    return res;
}
