#include <unistd.h>
#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include "display.h"

WINDOW *main_window;

/**
 * Initialize display variables and create main window
 */
void display_init()
{
    main_window = initscr();
    if (main_window == NULL) {
        fprintf(stderr, "%d - Could not initialize display\n", getpid());
    }

    cbreak();
    noecho();
    curs_set(0);
    clear();
}

/**
 * destroy display and display variables
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
