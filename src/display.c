#include <ncurses.h>
#include <string.h>
#include <assert.h>             /* for assert() */

#include "datatypes.h"
#include "display.h"
#include "util.h"
#include "map.h"


#define MENU_WIDTH 20
#define MENU_PADDING 2


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
    init_pair(COL_YEL_YEL,  COLOR_YELLOW,   COLOR_YELLOW);
    init_pair(COL_WHI_BLU,  COLOR_WHITE,    COLOR_BLUE);

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

void display_clear()
{
    clear();
    refresh();
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

    scale.y = 1;
    scale.x = 2;

    margin.y = MAX(0, ( LINES - scale.y * map -> size.y ) / 2);
    margin.x = MAX(0, ( COLS  - scale.x * map -> size.x ) / 2);

    wclear(map_window);

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

    /* scaled cursor position minus half the width gives the screen
     * start position */
    prefresh(map_window,
            MIN(scale.y * map -> cursor.y - (LINES / 2), scale.y * map -> size.y - LINES),
            MIN(scale.x * map -> cursor.x - (COLS  / 2), scale.x * map -> size.x - COLS),
            0, 0, LINES - 1, COLS - 2);
}

void display_msg_show(char *message)
{
    WINDOW *msg_win = subwin(display, 3, COLS / 3, 2, 2);
    assert(msg_win != NULL);

    wclear(msg_win);
    wbkgd(msg_win, COLOR_PAIR(COL_WHI_BLU));
    mvwprintw(msg_win, 0, 0, "%s", message);

    wrefresh(msg_win);
    /*delwin(msg_win);*/
}

void display_prompt_show(char *message)
{
    point_t size;
    WINDOW *msg_win;

    size.y = LINES / 3 * 2;
    size.x = COLS / 3 * 2;

    msg_win = subwin(display, size.y, size.x, LINES / 2 - size.y / 2, (COLS - size.x) / 2);
    assert(msg_win != NULL);

    wclear(msg_win);
    mvwprintw(msg_win, 0, 0, "%s", message);

    wrefresh(msg_win);
    delwin(msg_win);
}

void display_status_show(game_status_t status)
{
    wclear(status_bar);
    wbkgd(status_bar, COLOR_PAIR(COL_BLK_WHI));
    mvwprintw(status_bar, 0, 1, "Score: %d", status.score);
    wrefresh(status_bar);
}
