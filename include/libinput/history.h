#ifndef _LIBINPUT_HISTORY_H_
#define _LIBINPUT_HISTORY_H_

#define MAX_HISTORY_LENGTH 1024

#ifdef __cplusplus
extern "C" {
#endif

void enable_history(void);
void disable_history(void);

void add_history(char *);
void free_history(void);

char * previous_history(void);
char * next_history(void);

#ifdef __cplusplus
}
#endif

#endif /* _LIBINPUT_HISTORY_H_ */
