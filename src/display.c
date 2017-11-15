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


/**
 * The properties for various tiles
 */
struct {
    color_t color;
    char value;
} map_tile_props[TILE_SIZE];



boolean display_init()
{
    display = initscr();

    curs_set(0);                /* make cursor invisible */
    start_color();              /* use colors in the game */
    clear();                    /* clear the display */

    /* initialize color pairs */
    init_pair(COL_BLK_BLK,  COLOR_BLACK,    COLOR_BLACK);
    init_pair(COL_WHI_WHI,  COLOR_WHITE,    COLOR_WHITE);
    init_pair(COL_RED_RED,  COLOR_RED,      COLOR_RED);
    init_pair(COL_GRN_GRN,  COLOR_GREEN,    COLOR_GREEN);
    init_pair(COL_BLU_BLU,  COLOR_BLUE,     COLOR_BLUE);

    /* fill in tile properties */
    map_tile_props[TILE_BORDER].color = COL_BLK_BLK;
    map_tile_props[TILE_BORDER].value = ' ';
    map_tile_props[TILE_GRASS].color = COL_GRN_GRN;
    map_tile_props[TILE_GRASS].value = ' ';
    map_tile_props[TILE_BRICK].color = COL_BLK_BLK;
    map_tile_props[TILE_BRICK].value = ' ';
    map_tile_props[TILE_WATER].color = COL_BLK_BLK;
    map_tile_props[TILE_WATER].value = ' ';


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
    point_t scale;

    margin.x = ( COLS - map -> size.x ) / 2;
    margin.y = ( LINES - map -> size.y ) / 2;

    scale.x = 2;
    scale.y = 1;

    clear();

    for (int y = 0; y < map -> size.y; ++y) {
        for (int x = 0; x < map -> size.x; ++x) {
            wattron(map_window, COLOR_PAIR(
                        map_tile_props[map -> data[count]].color));

            mvwprintw(map_window,
                    scale.y * (margin.y + y),
                    scale.x * (margin.x + x),
                    "%c ", map_tile_props[map -> data[count]].value);

            wattroff(map_window, COLOR_PAIR(
                        map_tile_props[map -> data[count]].color));
            count++;
        }
    }

    wattron(map_window, COLOR_PAIR(COL_WHI_WHI));
    mvwprintw(map_window,
            scale.y * (margin.y + map -> cursor.y),
            scale.x * (margin.x + map -> cursor.x),
            "  ");
    wattroff(map_window, COLOR_PAIR(COL_WHI_WHI));

    wrefresh(map_window);
}
