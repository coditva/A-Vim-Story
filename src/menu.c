#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
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
    {show_help, "Help", "How to play"},
    {settings, "Settings", "Tweak to your liking"},
    {quit_game, "Quit", "Leave the game"},
    {size, NULL, NULL}
};

/* Menu size */
int menu_size = 0;

/* Variable for current choice */
int selected_item;

/* Window configurations */
unsigned int x_start, y_start, height, width;

/* Declare local functions */
void                menu_init(WINDOW *);
void                menu_select_next(WINDOW *);
void                menu_select_previous(WINDOW *);
int                 menu_take_input(WINDOW *window);


/* Display the menu and return choice */
enum MENU display_menu_get_choice()
{
    WINDOW *menu_window = NULL;
    enum MENU choice;

    height = 10;
    width = 20;
    x_start = (COLS - width) / 2;
    y_start = (LINES - height) / 2 + 2;
    
    menu_window = newwin(height, width, y_start, x_start);
    box(menu_window, ' ', ' ');

    /* calculate menu size */
    for (int i = 0; menu_items[i].key != size; ++i) menu_size++;

    menu_init(menu_window);

    selected_item = menu_size - 1;
    menu_select_next(menu_window);

    choice = menu_take_input(menu_window);

    delwin(menu_window);
    return choice;
}

/* Initialize the window with the options */
void menu_init(WINDOW *window)
{
    for (int i = 0; i < menu_size; ++i) {
        mvwprintw(window, 2 + i,
                (width - strlen(menu_items[i].text)) / 2,
                "%s", menu_items[i].text);
    }
    wrefresh(window);
}

/* Highlight the next option */
void menu_select_next(WINDOW *window)
{
    int prev_item;

    prev_item = selected_item;
    selected_item++;

    if (selected_item == menu_size) {
        selected_item = 0;
    }

    /* Remove highlight from prev item */
    mvwprintw(window, 2 + prev_item,
            (width - strlen(menu_items[prev_item].text)) / 2,
            "%s", menu_items[prev_item].text);

    /* Highlight selected item */
    wattron(window, A_STANDOUT);
    mvwprintw(window, 2 + selected_item,
            (width - strlen(menu_items[selected_item].text)) / 2,
            "%s", menu_items[selected_item].text);
    wattroff(window, A_STANDOUT);

    wrefresh(window);
}

/* Highlight the previous option */
void menu_select_previous(WINDOW *window)
{
    int prev_item;

    prev_item = selected_item;
    selected_item--;

    if (selected_item == -1) {
        selected_item = menu_size - 1;
    }

    /* Remove highlight from prev item */
    mvwprintw(window, 2 + prev_item,
            (width - strlen(menu_items[prev_item].text)) / 2,
            "%s", menu_items[prev_item].text);

    /* Highlight selected item */
    wattron(window, A_STANDOUT);
    mvwprintw(window, 2 + selected_item,
            (width - strlen(menu_items[selected_item].text)) / 2,
            "%s", menu_items[selected_item].text);
    wattroff(window, A_STANDOUT);

    wrefresh(window);
}

/* Take input and select appropriate choice */
int menu_take_input(WINDOW *window)
{
    int key;

    keypad(window, true);
    key = wgetch(window);
    while (key != ERR && key != 'q') {
        switch (key) {
            case 'j':
            case KEY_DOWN:
                menu_select_next(window);
                break;
            case 'k':
            case KEY_UP:
                menu_select_previous(window);
                break;
            case KEY_ENTER:
            case KEY_SEND:
            case 10:
                return selected_item;
                break;
        }

        key = wgetch(window);
    }
    return selected_item;
}
