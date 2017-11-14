#include <ncurses.h>
#include <string.h>

#include "config.h"
#include "datatypes.h"
#include "display.h"


#define MENU_WIDTH 20


WINDOW *display;                /* the main display */
WINDOW *map_window;             /* the map subwindow */
WINDOW *status_bar;             /* the status bar subwindow */
WINDOW *menu_window;            /* the menu subwindow */


/**
 * The labels for menu items
 */
char *menu_label[] = {
    "New Game",
    "Help",
    "Exit"
};


boolean display_init()
{
    display = initscr();

    curs_set(0);                /* make cursor invisible */
    start_color();              /* use colors */
    clear();                    /* clear the display */

    /* create status bar */
    status_bar = subwin(display, 1, COLS, 0, 0);
    if (!status_bar) return B_FALSE;

    /* create menu window of the smallest size possible in the center */
    menu_window = subwin(display,
            MENU_SIZE + 2,                  MENU_WIDTH,
            (LINES - MENU_SIZE) / 2 - 1,    (COLS - MENU_WIDTH) / 2);
    if (!menu_window) return B_FALSE;

    box(menu_window, '|', '-');           /* create a box around the window */

    /* create map window */
    map_window = subwin(display, 1, COLS, 0, 0);
    if (!map_window) return B_FALSE;

    return B_TRUE;
}

boolean display_destroy()
{
    /* delete all windows */
    delwin(map_window);
    delwin(menu_window);
    delwin(status_bar);
    delwin(display);

    /* end the display */
    endwin();

    return B_TRUE;
}

boolean display_refresh()
{
    if (wrefresh(map_window) == ERR) return B_FALSE;
    if (wrefresh(status_bar) == ERR) return B_FALSE;

    return B_TRUE;
}

void display_menu_show(enum menu_item selected)
{
    int x = 0;
    enum menu_item y = 0;

    mvwprintw(menu_window, 0, 1, "Menu");

    for (; y < MENU_SIZE; ++y) {
        x = ( MENU_WIDTH - strlen(menu_label[y]) ) / 2;

        if (y == selected) wstandout(menu_window);
        mvwprintw(menu_window, y + 1, x, menu_label[y]);
        if (y == selected) wstandend(menu_window);
    }

    wrefresh(menu_window);
}
