#include <ncurses.h>
#include <string.h>             /* for strlen() */
#include <assert.h>             /* for assert() */

#include "datatypes.h"
#include "interface.h"
#include "util.h"
#include "map.h"


#define MENU_WIDTH 20
#define MENU_PADDING 2


WINDOW *display = NULL;         /* the main display */
WINDOW *menu_window = NULL;     /* the menu subwindow */
WINDOW *map_window = NULL;      /* the map subwindow */
WINDOW *message_window = NULL;  /* the message subwindow */
WINDOW *prompt_window = NULL;   /* the prompt subwindow */
WINDOW *command_window = NULL;  /* the prompt subwindow */
WINDOW *status_bar = NULL;      /* the status bar subwindow */

char *menu_label[] = {          /* The labels for menu items */
    "New Game",
    "Help",
    "Exit"
};

struct {                        /* The properties for various tiles */
    color_t color;
} map_tile_props[TILE_SIZE];



boolean interface_init()
{
    display = NULL;
    point_t size;
    point_t start;

    display = initscr();

    curs_set(0);                /* make cursor invisible */
    start_color();              /* use colors in the game */
    noecho();                   /* do not echo the characters */
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


    /* create menu window in the center */
    size.y = MENU_SIZE + 2 * MENU_PADDING;
    size.x = MENU_WIDTH + 2 * MENU_PADDING;
    start.y = (LINES - MENU_SIZE ) / 2 - MENU_PADDING;
    start.x = (COLS  - MENU_WIDTH) / 2 - MENU_PADDING;
    if (!(menu_window = subwin(display, size.y, size.x, start.y, start.x)))
        return B_FALSE;

    /* create map window */
    if (!(map_window = newpad(MAPMAXY, MAPMAXX)))
        return B_FALSE;

    /* create message window at the left hand side of the display */
    size.y = LINES / 6;
    size.x = COLS  / 3;
    start.y = 2;
    start.x = 2;
    if (!(message_window = subwin(display, size.y, size.x, start.y, start.x)))
        return B_FALSE;

    /* create prompt window */
    size.y = LINES / 3 * 2;
    size.x = COLS  / 3 * 2;
    start.y = (LINES - size.y) / 2;
    start.x = (COLS  - size.x) / 2;
    if (!(prompt_window = subwin(display, size.y, size.x, start.y, start.x)))
        return B_FALSE;

    /* create status bar */
    size.y = 1;
    size.x = COLS;
    start.y = 0;
    start.x = 0;
    status_bar = subwin(display, 1, COLS, 0, 0);
    if (!(status_bar = subwin(display, size.y, size.x, start.y, start.x)))
        return B_FALSE;

    /* create command bar */
    size.y = 1;
    size.x = COLS;
    start.y = LINES - 1;
    start.x = 0;
    command_window = subwin(display, 1, COLS, 0, 0);
    if (!(command_window = subwin(display, size.y, size.x, start.y, start.x)))
        return B_FALSE;


    return B_TRUE;
}

boolean interface_destroy()
{
    /* delete all windows */
    delwin(status_bar);
    delwin(prompt_window);
    delwin(message_window);
    delwin(map_window);
    delwin(menu_window);
    delwin(display);

    /* end the display */
    endwin();

    return B_TRUE;
}

void interface_display_clear()
{
    clear();
    refresh();
}

void interface_display_menu(enum menu_item selected)
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

void interface_display_map(const map_t *map)
{
    int count = 0;
    point_t margin;
    map_tile_t tile;
    point_t scale;
    
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
    tile = map_get_tile(map -> cursor);
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

void interface_display_message(char *message)
{
    wclear(message_window);
    wbkgd(message_window, COLOR_PAIR(COL_WHI_BLU));
    mvwprintw(message_window, 0, 0, "%s", message);
    wrefresh(message_window);
}

void interface_display_prompt(char *message)
{
    wclear(prompt_window);
    mvwprintw(prompt_window, 0, 0, "%s", message);
    wrefresh(prompt_window);
    getch();
}

void interface_display_command(char *message)
{
    wclear(command_window);
    wbkgd(status_bar, COLOR_PAIR(COL_BLK_WHI));
    mvwprintw(command_window, 0, 0, "%s", message);
    wprintw(command_window, "_");
    wrefresh(command_window);
}

void interface_display_status(game_status_t status)
{
    wclear(status_bar);
    wbkgd(status_bar, COLOR_PAIR(COL_BLK_WHI));
    mvwprintw(status_bar, 0, 1, "Score: %d", status.score);
    wrefresh(status_bar);
}

input_key_t interface_input_key()
{
    return getch();
}
