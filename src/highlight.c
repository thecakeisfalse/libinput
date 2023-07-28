#include <libinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int use_highlight = 0;
static int patterns_length = 0;
static pattern_t patterns[MAX_PATTERNS_LENGTH];

void enable_highlight(void) {
    use_highlight = 1;
}

void disable_highlight(void) {
    use_highlight = 0;
}

void add_pattern(char * pattern, int color) {
    int index;

    if (patterns_length < MAX_PATTERNS_LENGTH) {
        patterns[patterns_length].color = color;
        patterns[patterns_length].pattern = (char *)calloc(MAX_PATTERN_LENGTH+1, sizeof(char));
        snprintf(patterns[patterns_length].pattern, MAX_PATTERN_LENGTH+1, "%s", pattern);
        patterns_length++;
    } else {
        for (index = 1; index < MAX_PATTERNS_LENGTH; index++) {
            snprintf(patterns[index-1].pattern, MAX_PATTERN_LENGTH+1, "%s", patterns[index].pattern);
            patterns[index-1].color = patterns[index].color;
        }

        snprintf(patterns[MAX_PATTERNS_LENGTH-1].pattern, MAX_PATTERN_LENGTH+1, "%s", pattern);
        patterns[MAX_PATTERNS_LENGTH-1].color = color;
    }
}

void free_patterns(void) {
    int index;

    for (index = 0; index < patterns_length; index++) {
        free(patterns[index].pattern);
    }

    patterns[0].pattern = NULL;
    patterns[0].color = 0;

    patterns_length = 0;
}

char * highlight(char * string) {
    char * result;

    pattern_t pattern = patterns[0];
    int pattern_offset = 0;
    int regmatch_offset = 0;

    regmatch_result_t ** regmatches;
    regmatch_result_t * regmatch;
    char * temp;
    char * temp_result;

    if (!use_highlight) {
        return string;
    }

    result = (char *)calloc(sizeof(char), strlen(string) * 20);

    strcpy(result, string);

    while (pattern_offset < patterns_length) {
        if (pattern.pattern == NULL) {
            continue;
        }

        regmatches = regmatch_all(string, pattern.pattern);
        regmatch_offset = 0;

        regmatch = *(regmatches+regmatch_offset);
        while (regmatch != NULL) {
            temp = (char *)calloc(sizeof(char), 1024);
            sprintf(temp, "\x1b[0;%dm%s\x1b[0m", pattern.color, regmatch->value);
            temp_result = replace(result, temp, regmatch->value);

            free(result);

            result = replace(temp_result, regmatch->value, temp);

            free(temp_result);

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
