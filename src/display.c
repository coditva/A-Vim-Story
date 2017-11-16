#include <ncurses.h>
#include <string.h>
#include <assert.h>             /* for assert() */

#include "datatypes.h"
#include "display.h"
#include "util.h"
#include "map.h"
#include "score.h"


#define MENU_WIDTH 20
#define MENU_PADDING 2

/* TODO: remove this */
#define MAPMAXX 900
#define MAPMAXY 900


WINDOW *display;                /* the main display */
WINDOW *map_window;             /* the map subwindow */
WINDOW *status_bar;             /* the status bar subwindow */
WINDOW *menu_window;            /* the menu subwindow */
WINDOW *msg_win;                /* the window for messages */


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
    init_pair(COL_BLK_WHI,  COLOR_BLACK,    COLOR_WHITE);
    init_pair(COL_BLK_BLU,  COLOR_BLACK,    COLOR_BLUE);
    init_pair(COL_YEL_YEL,  COLOR_YELLOW,    COLOR_YELLOW);

    /* fill in tile properties */
    map_tile_props[TILE_BORDER].color = COL_BLK_BLK;
    map_tile_props[TILE_GRASS].color = COL_GRN_GRN;
    map_tile_props[TILE_BRICK].color = COL_BLK_BLK;
    map_tile_props[TILE_WATER].color = COL_BLK_BLK;
    map_tile_props[TILE_LETTER].color = COL_BLK_WHI;
    map_tile_props[TILE_DOOR].color = COL_YEL_YEL;
    map_tile_props[TILE_GEM].color = COL_RED_RED;


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
    map_window = newpad(MAPMAXY, MAPMAXX);
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
    map_tile_t tile;

    margin.y = MAX(0, ( LINES - map -> size.y ) / 2);
    margin.x = MAX(0, ( COLS  - map -> size.x ) / 2);

    scale.y = 1;
    scale.x = 2;

    clear();

    for (int y = 0; y < map -> size.y; ++y) {
        for (int x = 0; x < map -> size.x; ++x) {
            tile = map -> data[count];

            wattron(map_window, COLOR_PAIR(map_tile_props[tile.type].color));
            mvwprintw(map_window,
                    margin.y + scale.y * y, margin.x + scale.x * x,
                    "%c ", tile.value);

            wattroff(map_window, COLOR_PAIR(map_tile_props[tile.type].color));

            count++;
        }
    }

    /* print the cursor */
    wattron(map_window, COLOR_PAIR(COL_BLK_BLU));

    /* get the tile under the cursor and print it's value */
    tile = map_get_tile(map, map -> cursor);
    mvwprintw(map_window,
            margin.y + scale.y * map -> cursor.y,
            margin.x + scale.x * map -> cursor.x,
            "%c ", tile.value);
    wattroff(map_window, COLOR_PAIR(COL_BLK_BLU));

    /* TODO: WHY DO WE NEED TO REFRESH? */
    refresh();

    /* scaled cursor position minus half the width gives the screen
     * start position */
    prefresh(map_window,
            scale.y * map -> cursor.y - (LINES / 2),
            scale.x * map -> cursor.x - (COLS  / 2),
            0, 0, LINES - 1, COLS - 2);
}

void display_msg_show(char *message)
{
    WINDOW *msg_win = subwin(display, 4, COLS - 4, 2, 2);
    assert(msg_win != NULL);

    mvwprintw(msg_win, 0, 0, "%s", message);

    wrefresh(msg_win);
    display_msg_close();
}

void display_msg_close()
{
    delwin(msg_win);
}

void display_status_show()
{
    wbkgd(status_bar, COLOR_PAIR(COL_BLK_WHI));
    mvwprintw(status_bar, 0, 1, "Score: %d", score_get());
    wrefresh(status_bar);
}
