#include <unistd.h>
#include <curses.h>
#include <assert.h>
#include <string.h>
#include "display.h"
#include "menu.h"

WINDOW *main_window;
int menu_selected;
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
