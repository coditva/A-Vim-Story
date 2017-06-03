#include <unistd.h>
#include <ncurses.h>
#include <assert.h>
#include <string.h>

#include "display.h"
#include "datatypes.h"
#include "util.h"

WINDOW *main_window;
WINDOW *map_window;
WINDOW *status_window;

/* local functions */
int display_get_color_pair(char);


/**
 * Return the main window
 * @return WINDOW* return the main window
 */
WINDOW * display_get_main_window()
{
    return main_window;
}

/**
 * Return the map window
 * @return WINDOW* return the map window
 */
WINDOW * display_get_map_window()
{
    return map_window;
}

/**
 * Return the status window
 * @return WINDOW* return the status window
 */
WINDOW * display_get_status_window()
{
    return status_window;
}

/**
 * Initializes the main window
 */
void display_set_main_window()
{
    main_window = initscr();
    if (main_window == NULL) {
        fprintf(stderr, "%d - Could not initialize display\n", getpid());
    }
}

/**
 * Initializes the map window
 */
void display_set_map_window()
{
    map_window = newpad(MAX_MAP_SIZE, MAX_MAP_SIZE);
    if (map_window == NULL) {
        fprintf(stderr, "%d - Could not initialize map window\n", getpid());
    }
}

/**
 * Initializes the status window
 */
void display_set_status_window()
{
    status_window = newwin(1, COLS, LINES - 1, 0);
    if (status_window == NULL) {
        fprintf(stderr, "%d - Could not initialize status window\n", getpid());
    }
}

/**
 * Initialize display variables and create main window
 */
void display_init()
{
    display_set_main_window();
    display_set_map_window();
    display_set_status_window();

    curs_set(0);
    start_color();
    clear();

    /* initialize color pairs */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_CYAN, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
}

/**
 * Destroy display and display variables
 */
void display_destroy()
{
    assert(main_window != NULL);

    delwin(main_window);
    main_window = NULL;
    endwin();
}

/**
 * Display the welcome message
 */
void display_welcome_msg()
{
    WINDOW *welcome_window = NULL;
    /* ASCII art for welcome message. Says: A Vim Story */
    char *_welcome_msg[] = {
    "            __      ___              _____ _                   ",
    "     /\\     \\ \\    / (_)            / ____| |                  ",
    "    /  \\     \\ \\  / / _ _ __ ___   | (___ | |_ ___  _ __ _   _ ",
    "   / /\\ \\     \\ \\/ / | | '_ ` _ \\   \\___ \\| __/ _ \\| '__| | | |",
    "  / ____ \\     \\  /  | | | | | | |  ____) | || (_) | |  | |_| |",
    " /_/    \\_\\     \\/   |_|_| |_| |_| |_____/ \\__\\___/|_|   \\__, |",
    "                                                          __/ |",
    "                                                         |___/ ",
    NULL
    };
    
    welcome_window = newwin(LINES, COLS, 0, 0);

    /* Display the ASCII art */
    wattron(welcome_window, A_BOLD);
    for (int i = 0; _welcome_msg[i] != NULL; ++i) {
        wmove(welcome_window, 1 + i, (COLS - strlen(_welcome_msg[i])) / 2);
        wprintw(welcome_window, "%s", _welcome_msg[i]);
    }
    wattroff(welcome_window, A_BOLD);

    wrefresh(welcome_window);
}

/**
 * Displays the map
 * @param map the map datatype
 * @param pos the position of the cursor datatype
 */
void display_map(const MAP map, const POSITION pos)
{
    WINDOW *map_window;

    map_window = display_get_map_window();
    wbkgd(map_window, COLOR_PAIR(display_get_color_pair('~')));

    for (int i = 0; i < map.sizey; ++i) {
        for (int j = 0; j < map.sizex; ++j) {

            char ch = *(map.map_data + i * map.sizex + j);
            int pair = display_get_color_pair(ch);

            wattron(map_window, COLOR_PAIR(pair));
            mvwprintw(map_window, i, j, "%c", ch);
            wattroff(map_window, COLOR_PAIR(pair));
        }
    }

    /* display the cursor */
    wmove(map_window, pos.y, pos.x);
    curs_set(2);

    /* set the status bar msg */
    wbkgd(status_window, COLOR_PAIR(6));
    mvwprintw(status_window, 0, 0, "status bar");
    wrefresh(status_window);

    /* display the map */
    prefresh(map_window,
            min(max(0, pos.y - LINES / 2), map.sizey - LINES),
            min(max(0, pos.x - COLS / 2), map.sizex - COLS),
            0, 0, LINES - 2, COLS - 1);
}

/**
 * Get the color pair from the list initialized int display_init() according
 * to the character to be displayed
 * @param char Character to be displayed
 * @return int pair number
 */
int display_get_color_pair(char ch)
{
    switch (ch) {
        case '~':
        case '+':
            return 2;
        case '`':
            return 3;
        case '$':
            return 4;
        case '#':
            return 5;
        default:
            return 1;
    }
}
