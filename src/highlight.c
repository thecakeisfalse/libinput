#include "input.h"
#include <stdlib.h>
#include <string.h>

static int use_highlight = 0;

static pattern_t patterns[1025] = {
    {NULL, -1}
};

static int patterns_length = 0;

int highlight_enabled(void) {
     return use_highlight;
}

void enable_highlight(void) {
    use_highlight = 1;
    patterns[1024].pattern = NULL;
    patterns[1024].color = -1;
}

void add_pattern(char * pattern, int color) {
    int index = 0;

    if (!use_highlight) {
        return;
    }

    if (patterns_length < 1024) {
        patterns[patterns_length].color = color;
        patterns[patterns_length].pattern = (char *)calloc(1024, sizeof(char));
        strncpy(patterns[patterns_length].pattern, pattern, 1024);
    } else {
        for (index = 1; index < 1024; index++) {
            strncpy(patterns[index-1].pattern, patterns[index].pattern, 1024);
            patterns[index-1].color = patterns[index].color;
        }
        strncpy(patterns[1023].pattern, pattern, 1024);
        patterns[1023].color = color;
    }
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
