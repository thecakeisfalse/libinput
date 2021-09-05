#ifndef _LIBINPUT_REGEX_H_
#define _LIBINPUT_REGEX_H_

#define REGMATCH_RESULT_MAX 16

#ifdef __cplusplus
extern "C" {
#endif

struct regmatch_result {
    int start;
    int end;
    char * value;
};

typedef struct regmatch_result regmatch_result_t;

regmatch_result_t * regmatch(char *, char *);
regmatch_result_t ** regmatch_all(char *, char *);
void regmatchfree(regmatch_result_t *);

#ifdef __cplusplus
}
#endif

#endif /* _LIBINPUT_REGEX_H_ */
