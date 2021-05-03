#include "input.h"

void main() {
    enable_highlight();
    add_pattern("12", 34);
    add_pattern("34", 35);
    printf("%s\n", read_input("> "));
}
