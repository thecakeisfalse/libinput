#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "libinput.h"

regmatch_result_t * regmatch(char * string, char * pattern) {
    static regex_t re;
    regmatch_t match;
    regmatch_result_t * regmatch_result = NULL;
    int length = 0;
    static char * previous_pattern = NULL;

    if (previous_pattern == NULL) {
        previous_pattern = (char *)calloc(sizeof(char), 1024);
    }

    if (strcmp(pattern, previous_pattern)) {
        strcpy(previous_pattern, pattern);
        regfree(&re);

        if (strcmp(pattern, "") == 0) {
            free(previous_pattern);
            previous_pattern = NULL;
            return NULL;
        }

        if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
            printf("Warning: failed to compile regular expression\n");
            regfree(&re);
            return regmatch_result;
        }

    }

    regmatch_result = (regmatch_result_t *)malloc(sizeof(regmatch_result_t));

    if (regmatch_result == NULL) {
        printf("Fatal: failed to allocte %lu bytes.\n", sizeof(regmatch_result_t));
        free(regmatch_result);
        exit(1);
    }

    regmatch_result->start = -1;
    regmatch_result->end = -1;
    regmatch_result->value = NULL;

    if (regexec(&re, string, 1, &match, 0) == 0) {
        regmatch_result->start = match.rm_so;
        regmatch_result->end = match.rm_eo;

        length = match.rm_eo - match.rm_so;
        regmatch_result->value = (char *)calloc(sizeof(char), length+1);
        memcpy(regmatch_result->value, string+match.rm_so, length);
        regmatch_result->value[length] = '\0';
    }

    return regmatch_result;
}

regmatch_result_t ** regmatch_all(char * string, char * pattern) {
    int regmatches_size = REGMATCH_RESULT_MAX;
    int real_regmatches_size = 0;
    int previous_end = 0;
    regmatch_result_t * regmatch_result = NULL;
    regmatch_result_t ** all_regmatches = NULL;

    all_regmatches = (regmatch_result_t **)malloc(sizeof(regmatch_result_t) * regmatches_size);
    if (all_regmatches == NULL) {
        printf("Fatal: failed to allocte %lu bytes.\n", sizeof(regmatch_result_t) * regmatches_size);
        free(all_regmatches);
        exit(1);
    }

    do {
        regmatch_result = regmatch(string+previous_end, pattern);
        if (regmatch_result->start == -1 || regmatch_result->value == NULL) {
            regmatchfree(regmatch_result);
            break;
        }

        if (real_regmatches_size >= regmatches_size) {
            regmatches_size <<= 1;
            printf("REALLOC %d\n", regmatches_size);

            all_regmatches = (regmatch_result_t **)realloc(all_regmatches, sizeof(regmatch_result_t) * regmatches_size);
            if (all_regmatches == NULL) {
                printf("Fatal: failed to allocte %lu bytes.\n", sizeof(regmatch_result_t) * regmatches_size);
                free(all_regmatches);
                exit(1);
            }
        }

        regmatch_result->end += previous_end;
        regmatch_result->start += previous_end;

        *(all_regmatches+real_regmatches_size) = regmatch_result;
        previous_end = regmatch_result->end;

        real_regmatches_size++;
    } while (1);

    regmatch("", "");
    *(all_regmatches+real_regmatches_size) = NULL;

    return all_regmatches;
}

void regmatchfree(regmatch_result_t * regmatch_result) {
    if (regmatch_result != NULL) {
        if (regmatch_result->value != NULL) {
            free(regmatch_result->value);
        }
        free(regmatch_result);
    }
}
