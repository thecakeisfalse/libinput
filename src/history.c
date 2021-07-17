#include "input.h"
#include <string.h>
#include <stdlib.h>

static int use_history = 0;

static int history_size = 0, history_offset = 0;
static char *history[1024];

int history_enabled(void) {
    return use_history;
}

void enable_history(void) {
    use_history = 1;
}

void add_history(char * string) {
    int index;

    if (!use_history) {
        return;
    }
    if (history_size < 1024) {
        history[history_size] = (char*)calloc(1024, sizeof(char));
        strncpy(history[history_size], string, 1024);
        history_size++;
    } else {
        for (index = 1; index < 1024; index++) {
            strncpy(history[index - 1], history[index], 1024);
        }
        strncpy(history[1023], string, 1024);
    }
}

char * previous_history(void) {
    return (history_offset < history_size && use_history) ? history[history_offset++] : NULL;
}

char * next_history(void) {
    return (history_offset && use_history) ? history[history_offset--] : NULL;
}
