#include <libinput.h>
#include <stdlib.h>
#include <string.h>

static int use_history = 0;

static int history_size = 0;
static int history_index = 0;
static char * history[MAX_HISTORY_LENGTH];

void enable_history(void) {
    use_history = 1;
}

void disable_history(void) {
    use_history = 0;
}

void add_history(char * string) {
    int index;
    if (!use_history) {
        return;
    }

    if (history_size < MAX_HISTORY_LENGTH) {
        history[history_size] = (char *)calloc(1024, sizeof(char));
        strncpy(history[history_size], string, 1024);
        history_size++;
        history_index = history_size;
    } else {
        for (index = 1; index < MAX_HISTORY_LENGTH; index++) {
            strncpy(history[index-1], history[index], 1024);
        }
        strncpy(history[MAX_HISTORY_LENGTH-1], string, 1024);
    }
}

void free_history(void) {
    int index;

    for (index = 0; index < history_size; index++) {
        free(history[index]);
    }

    disable_history();
}

char * previous_history(void) {
    if (history_index > 0) {
        return history[--history_index];
    }
    return NULL;
}

char * next_history(void) {
    if (history_index < MAX_HISTORY_LENGTH) {
        return history[history_index++];
    }
    return NULL;
}
