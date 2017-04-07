#ifndef DISPLAY_H
#define DISPLAY_H

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


/* Initialize screen and create the main window */
void                display_init();

/* Destroy the main window */
void                display_destroy();

/* Show the welcome message */
void                display_welcome_msg();

/* Show the help window */
void                display_show_help();

/* Show the quit message */
void                display_quit_msg();


/* Show the menu and return the selected item according to the MENU enum */
int                 display_get_action();

#endif /* DISPLAY_H */
