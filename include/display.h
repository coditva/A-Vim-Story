#ifndef DISPLAY_H_ZEJHMS7R
#define DISPLAY_H_ZEJHMS7R


/**
 * Initialize the display
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean display_init();


/**
 * Destroy the display and clear all allocated space
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean display_destroy();


/**
 * Refreshes and redraws the whole window
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean display_refresh();


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void display_menu_show(enum menu_item);


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void display_map_show(map_t *);


/**
 * Show the given message in a popup msg window
 * @param The message to show
 */
void display_msg_show(char *);


/**
 * Show the status bar
 */
void display_status_show(game_status_t);

#endif /* end of include guard: DISPLAY_H_ZEJHMS7R */
