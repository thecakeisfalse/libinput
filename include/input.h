#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>

#define REGMATCH_MAX 1024

struct pattern {
    char * pattern;
    int color;
};

typedef struct pattern pattern_t;

struct regmatch_result {
    int start;
    int end;
    char * value;
};

typedef struct regmatch_result regmatch_result_t;

char getch(void);

char * read_input(char * prompt);

void enable_highlight(void);
int highlight_enabled(void);
void add_pattern(char * pattern, int color);
char * highlight(char * line);

regmatch_result_t * regmatch(char * string, char * pattern);
void regmatchfree(regmatch_result_t * result);
regmatch_result_t ** regmatch_all(char * string, char * pattern);

char * replace(char * string, char * was, char * now);
char * sdup(char * string);

#endif /* _INPUT_H_ */
