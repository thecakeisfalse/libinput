#ifndef _LIBINPUT_HIGHLIGHT_H_
#define _LIBINPUT_HIGHLIGHT_H_

#define MAX_PATTERNS_LENGTH 1024
#define MAX_PATTERN_LENGTH 256

#ifdef __cplusplus
extern "C" {
#endif

struct pattern {
    char * pattern;
    int color;
};

typedef struct pattern pattern_t;

void enable_highlight(void);
void disable_highlight(void);

void add_pattern(char *, int);
void free_patterns(void);

char * highlight(char *);

#ifdef __cplusplus
}
#endif

#endif /* _LIBINPUT_HIGHLIGHT_H_ */
