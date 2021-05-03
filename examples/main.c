#include "input.h"

void main() {
    enable_highlight();
    enable_history();
    add_history("Hello, World!");
    printf("%s\n", read_input("> "));
}
