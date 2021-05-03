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
        history[history_size] = (char*)malloc(sizeof(char)*1024);
        strcpy(history[history_size], string);
        history_size++;
    } else {
        free(history[0]);
        for (index = 1; index < 1024; index++) {
            history[index - 1] = history[index];
        }
        strcpy(history[1023], string);
    }
}

char * previous_history(void) {
    return (history_offset < history_size && use_history) ? history[history_offset++] : NULL;
}

char * next_history(void) {
    return (history_offset && use_history) ? history[history_offset--] : NULL;
}
