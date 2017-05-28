#include <unistd.h>
#include <ncurses.h>
#include <assert.h>
#include <string.h>

#include "display.h"
#include "datatypes.h"

WINDOW *main_window;
WINDOW *map_window;

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
    map_window = newwin(LINES, COLS, 0, 0);
    if (map_window == NULL) {
        fprintf(stderr, "%d - Could not initialize map window\n", getpid());
    }
}

/**
 * Initialize display variables and create main window
 */
void display_init()
{
    display_set_main_window();
    display_set_map_window();

    curs_set(0);
    start_color();
    clear();

    /* initialize color pairs */
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
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

    /* display the map */
    wrefresh(map_window);
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
            return 1;
        case '+':
            return 2;
        default:
            return 0;
    }
}
