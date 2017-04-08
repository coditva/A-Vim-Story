#ifndef DISPLAY_H
#define DISPLAY_H

#include "menu.h"


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
enum MENU           display_get_action();

#endif /* DISPLAY_H */
