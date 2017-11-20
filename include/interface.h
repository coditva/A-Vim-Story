#ifndef INTERFACE_H_N7LPPW8B
#define INTERFACE_H_N7LPPW8B


/**
 * Initialize the display
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean interface_init();


/**
 * Destroy the display and clear all allocated space
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean interface_destroy();


/**
 * Clear and refresh the whole display
 */
void interface_display_clear();


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void interface_display_menu(enum menu_item);


/**
 * Refreshes and shows the menu on top of all windows
 * @param The item to show as selected
 */
void interface_display_map(const map_t *);


/**
 * Show the given message in a status bar at the bottom
 * @param The message to show
 */
void interface_display_command(char *command);


/**
 * Show the given message in a popup msg window
 * @param The message to show
 */
void interface_display_message(char *);


/**
 * Show a prompt window with the given message
 * @param The message to show
 */
void interface_display_prompt(char *);


/**
 * Show the status bar
 */
void interface_display_status(game_status_t);


/**
 * Wait for a key press and return it
 * @return The key pressed
 */
input_key_t interface_input_key();


#endif /* end of include guard: INTERFACE_H_N7LPPW8B */
