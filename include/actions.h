#ifndef ACTIONS_H
#define ACTIONS_H

/* Initialize app */
void                actions_init();

/* Call display to show a menu and show get action. Call action accordingly */
void                actions_select_action();

/* Start a new game */
void                actions_new_game();

/* Load a previous saved game */
void                actions_load_game();

/* Save the game and return to the menu */
void                actions_save_game();

/* Show help msg */
void                actions_show_help();

/* Call display to show settings window */
void                actions_settings();

/* Show the quit message and exit */
void                actions_quit();

#endif /* ACTIONS_H */
