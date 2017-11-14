#include <ncurses.h>
#include <string.h>
#include <assert.h>             /* for assert() */

#include "datatypes.h"
#include "display.h"


#define MENU_WIDTH 20
#define MENU_PADDING 2


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
    clear();                    /* clear the display */

    /* create status bar */
    status_bar = subwin(display, 1, COLS, 0, 0);
    if (!status_bar) return B_FALSE;

    /* create menu window in the center */
    menu_window = subwin(display,
            MENU_SIZE + 2 * MENU_PADDING,               /* size y  */
            MENU_WIDTH + 2 * MENU_PADDING,              /* size x  */
            (LINES - MENU_SIZE) / 2 - MENU_PADDING,     /* start y */
            (COLS - MENU_WIDTH) / 2 - MENU_PADDING);    /* start x */
    if (!menu_window) return B_FALSE;

    /* create map window */
    map_window = subwin(display, LINES - 1, COLS, 1, 0);
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

    wclear(menu_window);
    box(menu_window, '|', '-');           /* create a box around the window */

    for (; y < MENU_SIZE; ++y) {
        x = MENU_PADDING + ( MENU_WIDTH - strlen(menu_label[y]) ) / 2;

        if (y == selected) wstandout(menu_window);
        mvwprintw(menu_window, y + 1 + MENU_PADDING - 1, x, menu_label[y]);
        if (y == selected) wstandend(menu_window);
    }

    wrefresh(menu_window);
}

void display_map_show(map_t *map)
{
    int count = 0;
    point_t margin;

    margin.x = ( COLS - map -> size.x ) / 2;
    margin.y = ( LINES - map -> size.y ) / 2;

    clear();

    for (int y = 0; y < map -> size.y; ++y) {
        for (int x = 0; x < map -> size.x; ++x) {
            switch (map -> data[count]) {
                case TILE_BORDER:
                    mvwprintw(map_window, margin.y + y, margin.x + x, "%c", '*');
                    break;
                case TILE_WATER:
                    mvwprintw(map_window, margin.y + y, margin.x + x, "%c", '~');
                    break;
                case TILE_GRASS:
                    mvwprintw(map_window, margin.y + y, margin.x + x, "%c", ' ');
                    break;
                case TILE_BRICK:
                    mvwprintw(map_window, margin.y + y, margin.x + x, "%c", '#');
                    break;
                default:
                    assert(0);      /* this should never happen */
            }
            count++;
        }
    }

    mvwprintw(map_window,
            margin.y + map -> cursor.y,
            margin.x + map -> cursor.x,
            "C");

    wrefresh(map_window);
}
