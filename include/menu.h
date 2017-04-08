#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H


#include<ncurses.h>

/* Define what each menu option is */
enum MENU {
    new_game,
    load_game,
    save_game,
    show_help,
    settings,
    quit_game,
    size
};

/* Display the menu on the given window and return choice */
enum MENU           display_menu_get_choice();

#endif /* DISPLAY_MENU_H */
