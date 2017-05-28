#include <ncurses.h>

#include "input.h"
#include "datatypes.h"

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
 * If the user is quitting, a position of (0, 0) is returned.
 * @param WINDOW* the window from which to get keypress
 * @return POSITION with the key value
 */
POSITION input_get_new_pos(WINDOW *win, POSITION pos)
{
    int key;

    key = wgetch(win);

    /* change position accordingly
     * TODO: use lookup table in the future */
    switch (key) {
        case 'j':
            pos.y++;
            break;
        case 'k':
            pos.y--;
            break;
        case 'h':
            pos.x--;
            break;
        case 'l':
            pos.x++;
            break;
        case 'q':
            pos.x = 0;
            pos.y = 0;
        default:
            /* no action if key is invalid */
            break;
    }

    return pos;
}
