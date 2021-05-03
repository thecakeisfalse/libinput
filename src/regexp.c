#include "input.h"
#include <regex.h>
#include <stdlib.h>
#include <string.h>

regmatch_result_t * regmatch(char * string, char * pattern) {
    regex_t re;
    regmatch_t match;
    regmatch_result_t * result = (regmatch_result_t *)malloc(sizeof(regmatch_result_t));

    result->start = -1;
    result->end = -1;
    result->value = NULL;

    regcomp(&re, pattern, REG_EXTENDED);
    if (regexec(&re, string, 1, &match, 0) == 0) {
        result->start = match.rm_so;
        result->end = match.rm_eo;
        result->value = (char *)calloc(sizeof(char), (result->end-result->start));
        memcpy(result->value, string+result->start, sizeof(char)*(result->end-result->start));
    }
    regfree(&re);

    return result;
}

void regmatchfree(regmatch_result_t * result) {
    free(result->value);
    free(result);
}

regmatch_result_t ** regmatch_all(char * string, char * pattern) {
    int offset = 0;
    char * dup = sdup(string);
    regmatch_result_t ** result = (regmatch_result_t **)malloc(sizeof(regmatch_result_t) * REGMATCH_MAX);
    regmatch_result_t * regmatch_result;

    int previous_end = 0;

    while (1) {
        regmatch_result = regmatch(dup+previous_end, pattern);

        if (regmatch_result->start == -1) {
            break;
        }
        regmatch_result->end += previous_end;
        regmatch_result->start += previous_end;

        *(result+offset) = regmatch_result;
        previous_end = regmatch_result->end;

        offset++;
    }

    *(result+offset) = NULL;

    return result;
}
