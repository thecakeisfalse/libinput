#ifndef _LIBINPUT_UNIX_H_
#define _LIBINPUT_UNIX_H_

#define ESCAPE      27
#define ARROW_UP    65
#define ARROW_DOWN  66
#define ARROW_LEFT  67
#define ARROW_RIGHT 68

#ifdef __cplusplus
extern "C" {
#endif

char getch(void);

#ifdef __cplusplus
}
#endif

#endif /* _LIBINPUT_UNIX_H_ */
