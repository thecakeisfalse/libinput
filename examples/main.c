#include "libinput.h"
#include <stdlib.h>
#include <stdio.h>

void main(void) {
    char * string = NULL;
    string = read_input("> ");

    char * d = replace(string, "1", "2");
    free(d);

    regmatch_result_t ** r = regmatch_all(string, "[0-9]");

    int i = 0;
    while (r[i] != NULL) {
        regmatchfree(r[i]);
        i++;
    }

    free(r);
    printf("%s\n", string);
    free(string);
}
