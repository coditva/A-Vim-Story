#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "menu.h"

/* Define a struct for options */
struct option
{
    enum MENU key;
    char *text;
    char *desc;
};

/* Define options */
struct option menu_items[] = {
    {new_game, "New game", "Start a new game"},
    {load_game, "Load game", "Load a new game"},
    {save_game, "Save game", "Save this game"},
    {settings, "Settings", "Tweak to your liking"},
    {help, "Help", "How to play"},
    {quit, "Quit", "Leave the game"},
    {size, NULL, NULL}
};

/* Menu size */
int menu_size = 0;

/* Variable for current choice */
int selected_item;

/* Window configurations */
unsigned int x_start, y_start, height, width;

/* Pointer for menu window */
WINDOW *menu_window = NULL;

/* Pointer for menu help text window */
WINDOW *menu_help_window = NULL;

/* Declare local functions */
void                menu_init();
void                menu_select_next();
void                menu_select_previous();
void                menu_show_help_msg(enum MENU);
int                 menu_take_input();


/**
 * Display the menu and return choice
 */
enum MENU menu_get_choice()
{
    enum MENU choice;

    height = 10;
    width = 20;
    x_start = (COLS - width) / 2;
    y_start = (LINES - height) / 2 + 2;
    
    /* Create window */
    menu_window = newwin(height, width, y_start, x_start);
    menu_help_window = newwin(1, COLS - 1, LINES - 1, 0);
    if (menu_window == NULL || menu_help_window == NULL) {
        fprintf(stderr, "%d - %s\n", getpid(), "Unable to create menu window");
        exit(EXIT_FAILURE);
    }
    box(menu_window, '|', '-');

    /* calculate menu size */
    menu_size = 0;
    for (int i = 0; menu_items[i].key != size; ++i) menu_size++;

    menu_init(menu_window);

    /* Select last item and call select_next to highlight first item */
    selected_item = menu_size - 1;
    menu_select_next(menu_window);

    choice = menu_take_input(menu_window);

    delwin(menu_window);
    delwin(menu_help_window);
    menu_window = NULL;
    menu_help_window = NULL;

    return choice;
}

/**
 * Initialize the window with the options
 */
void menu_init()
{
    assert(menu_window != NULL);

    for (int i = 0; i < menu_size; ++i) {
        mvwprintw(menu_window, 2 + i,
                (width - strlen(menu_items[i].text)) / 2,
                "%s", menu_items[i].text);
    }
    wrefresh(menu_window);
}

/**
 * Highlight the next option
 */
void menu_select_next()
{
    int prev_item;

    assert(menu_window != NULL);

    prev_item = selected_item;
    selected_item++;

    if (selected_item == menu_size) {
        selected_item = 0;
    }

    /* Remove highlight from prev item */
    mvwprintw(menu_window, 2 + prev_item,
            (width - strlen(menu_items[prev_item].text)) / 2,
            "%s", menu_items[prev_item].text);

    /* Highlight selected item */
    wattron(menu_window, A_STANDOUT);
    mvwprintw(menu_window, 2 + selected_item,
            (width - strlen(menu_items[selected_item].text)) / 2,
            "%s", menu_items[selected_item].text);
    wattroff(menu_window, A_STANDOUT);

    wrefresh(menu_window);

    /* Add a window at the bottom displaying help message */
    menu_show_help_msg(selected_item);
}

/**
 * Highlight the previous option
 */
void menu_select_previous()
{
    int prev_item;

    assert(menu_window != NULL);

    prev_item = selected_item;
    selected_item--;

    if (selected_item == -1) {
        selected_item = menu_size - 1;
    }

    /* Remove highlight from prev item */
    mvwprintw(menu_window, 2 + prev_item,
            (width - strlen(menu_items[prev_item].text)) / 2,
            "%s", menu_items[prev_item].text);

    /* Highlight selected item */
    wattron(menu_window, A_STANDOUT);
    mvwprintw(menu_window, 2 + selected_item,
            (width - strlen(menu_items[selected_item].text)) / 2,
            "%s", menu_items[selected_item].text);
    wattroff(menu_window, A_STANDOUT);

    wrefresh(menu_window);

    /* Add a window at the bottom displaying help message */
    menu_show_help_msg(selected_item);
}

/**
 * Show the help text at the bottom of the screen
 * @param item The item to show help text for
 */
void menu_show_help_msg(enum MENU item)
{
    assert(menu_help_window != NULL);

    wclear(menu_help_window);
    wmove(menu_help_window, 0, COLS - strlen(menu_items[item].desc) - 1);
    wprintw(menu_help_window, "%s", menu_items[item].desc);

    wrefresh(menu_help_window);
}

/* Take input and select appropriate choice
 * @return selected_item
 */
int menu_take_input()
{
    int key;

    assert(menu_window != NULL);

    keypad(menu_window, true);
    key = wgetch(menu_window);
    while (key != ERR) {
        switch (key) {
            case 'j':
            case KEY_DOWN:
                menu_select_next(menu_window);
                break;
            case 'k':
            case KEY_UP:
                menu_select_previous(menu_window);
                break;
            case KEY_ENTER:
            case KEY_SEND:
            case 10:
                return selected_item;
                break;
        }

        key = wgetch(menu_window);
    }
    keypad(menu_window, false);

    return selected_item;
}
