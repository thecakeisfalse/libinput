#include "input.h"
#include <stdlib.h>
#include <string.h>

static int use_highlight = 0;

static pattern_t patterns[1024] = {
    {NULL, -1}
};

int patterns_length = 0;

int highlight_enabled(void) {
     return use_highlight;
}

void enable_highlight(void) {
    use_highlight = 1;
}

void add_pattern(char * pattern, int color) {
    pattern_t ptrn;
    int index = 0;

    ptrn.pattern=pattern;
    ptrn.color=color;

    for (index = patterns_length-1; index >= 0; index--) {
        patterns[index+1] = patterns[index];
    }
    patterns[0] = ptrn;

    patterns_length++;
}

char * highlight(char * string) {
    char * result = (char *)calloc(sizeof(char), strlen(string) * 20);
    pattern_t pattern = patterns[0];
    int pattern_offset = 0;
    int regmatch_offset = 0;

    regmatch_result_t ** regmatches;
    regmatch_result_t * regmatch;
    char * temp;

    strcpy(result, string);

    while (pattern.pattern != NULL) {
        regmatches = regmatch_all(string, pattern.pattern);
        regmatch_offset = 0;

        regmatch = *(regmatches+regmatch_offset);
        while (regmatch != NULL) {
            temp = (char *)calloc(sizeof(char), 1024);
            sprintf(temp, "\x1b[1;%dm%s\x1b[0m", pattern.color, regmatch->value);
            result = replace(result, temp, regmatch->value);
            result = replace(result, regmatch->value, temp);

            regmatchfree(regmatch);
            regmatch_offset++;
            regmatch = *(regmatches+regmatch_offset);
            free(temp);
        }

        free(regmatches);

        pattern_offset++;
        pattern = *(patterns+pattern_offset);
    }

    return result;
}
