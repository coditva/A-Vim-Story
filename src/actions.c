#include <unistd.h>
#include <stdlib.h>
#include "actions.h"
#include "display.h"
#include "project.h"

/*
 * Initialize application and display and get things going.
 */
void actions_init()
{
    project_set_title("A Vim Story");
    display_init();

    display_welcome_msg();
    actions_select_action();

    display_destroy();
}

/*
 * Select next action to take. Calls display to get the action from the menu.
 */
void actions_select_action()
{
    switch (display_get_action()) {
        case new_game:
            actions_new_game();
            break;
        case load_game:
            actions_load_game();
            break;
        case save_game:
            actions_save_game();
            break;
        case show_help:
            actions_show_help();
            break;
        case settings:
            actions_settings();
            break;
        case quit_game:
            actions_quit();
            break;
        default:
            fprintf(stderr, "%d: Wrong choice sent by display. Exiting.\n",
                    getpid());
            exit(EXIT_FAILURE);
    }
}

/*
 * Start a new game
 */
void actions_new_game()
{
}

/*
 * Load a previous saved game
 */
void actions_load_game()
{
}

/*
 * Save the game and return to the menu
 */
void actions_save_game()
{
}

/*
 * Show help message
 */
void actions_show_help()
{
    display_show_help();
    actions_select_action();
}

/*
 * Call display to show settings window
 */
void actions_settings()
{
}

/*
 * Show quit message and exit
 */
void actions_quit()
{
    display_quit_msg();
    display_destroy();
    exit(EXIT_SUCCESS);
}
