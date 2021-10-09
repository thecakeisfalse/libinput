#include "libinput.h"
#include <stdlib.h>
#include <stdio.h>

void main(void) {
    char * string = NULL;
    enable_highlight();
    string = read_input("> ");

    printf("%s\n", string);
    add_pattern("1", 31);

    char * test = highlight(string);
    printf("%s\n", test);

    free_patterns();
    free(test);
    free(string);
}
