#include <ncurses.h>

#include "input.h"

/**
 * Initialize keyboard
 */
void input_init()
{
    keypad(stdscr, TRUE);

    noecho();
    cbreak();
    curs_set(0);
}

/**
 * Request and get a key press from the given window
 * @param WINDOW* the window from which to get keypress
 * @return integer with the key value
 */
int input_get_key(WINDOW *win)
{
    int key;
    key = wgetch(win);
    return key;
}
