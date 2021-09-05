#ifndef _LIBINPUT_H_
#define _LIBINPUT_H_

#include <stddef.h>

#include "libinput-regex.h"

#ifdef _WIN32
#  include "libinput-windows.h"
#else
#  include "libinput-unix.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

char * read_input(char *);
char * replace(char *, char *, char *);

#ifdef __cplusplus
}
#endif

#endif /* _LIBINPUT_H_ */
