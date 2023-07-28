#include <libinput.h>

#ifndef _WIN32

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char getch(void) {
    char chr;
    struct termios old_term, new_term;

    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    chr = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    return chr;
}

#endif
