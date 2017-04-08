#include <unistd.h>
#include <curses.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"
#include "menu.h"

WINDOW *main_window;
int menu_selected;

/* ASCII art for welcome message. Says: A Vim Story */
char *_welcome_msg[] = {
"            __      ___              _____ _                   ",
"     /\\     \\ \\    / (_)            / ____| |                  ",
"    /  \\     \\ \\  / / _ _ __ ___   | (___ | |_ ___  _ __ _   _ ",
"   / /\\ \\     \\ \\/ / | | '_ ` _ \\   \\___ \\| __/ _ \\| '__| | | |",
"  / ____ \\     \\  /  | | | | | | |  ____) | || (_) | |  | |_| |",
" /_/    \\_\\     \\/   |_|_| |_| |_| |_____/ \\__\\___/|_|   \\__, |",
"                                                          __/ |",
"                                                         |___/ "
};


/*
 * Initialize screen and create the main window
 */
void display_init()
{
    main_window = initscr();
    box(main_window, '|', '-');

    cbreak();
    noecho();
    curs_set(0);
    clear();
}

/*
 * Destroy the main window
 */
void display_destroy()
{
    assert(main_window != NULL);

    delwin(main_window);
    main_window = NULL;
    endwin();
}

/*
 * Show the welcome message
 */
void display_welcome_msg()
{
    assert(main_window != NULL);

    /* Display the ASCII art */
    wattron(main_window, A_BOLD);
    for (int i = 0; _welcome_msg[i] != NULL; ++i) {
        wmove(main_window, 1 + i, (COLS - strlen(_welcome_msg[i])) / 2);
        wprintw(main_window, "%s", _welcome_msg[i]);
    }
    wattroff(main_window, A_BOLD);

    wrefresh(main_window);
}

/*
 * Show the help window
 */
void display_show_help()
{
    WINDOW *help_window = NULL;
    char *help_instr[] = {
        "1. Point one goes here. this is the best place to plave the point one.",
        "   you have to place point one here. This is actually a way to show",
        "   that this is how a multiline point should be.",
        "2. Here we have the point two",
        "3. We have the two point three here",
        "4. This is just point four. Hurray!",
        NULL
    };


    help_window = newwin(LINES, COLS, 0, 0);
    if (help_window == NULL) {
        fprintf(stderr, "%d - %s\n", getpid(), "Unable to attach help window");
        exit(EXIT_FAILURE);
    }

    /* The actual help content */
    char *help_msg;
    wattron(help_window, A_BOLD);
    help_msg = "Help and instructions";
    mvwprintw(help_window, 2, (COLS - strlen(help_msg)) / 2, "%s", help_msg);
    wattroff(help_window, A_BOLD);

    for (int i = 0; help_instr[i] != NULL; ++i) {
        mvwprintw(help_window, 5 + i, 2, "%s\n", help_instr[i]);
    }

    wrefresh(help_window);

    /* Capture keyboard and dont leave until 'q' is pressed */
    keypad(help_window, true);
    while ((getch()) != 'q') {;}
    keypad(help_window, false);

    delwin(help_window);
    help_window = NULL;

    /* Clear the help window from the screen */
    touchwin(main_window);
    wrefresh(main_window);
}

/*
 * Show the quit message
 */
void display_quit_msg()
{
}

/*
 * Show the menu and return the selected item according to the MENU enum
 */
enum MENU display_get_action()
{
    return display_menu_get_choice();
}
