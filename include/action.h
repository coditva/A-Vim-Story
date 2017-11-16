#ifndef ACTION_H_D9AS6ZWN
#define ACTION_H_D9AS6ZWN

/**
 * Take a key as input and update the map checking if the move is valid or not
 * @param The map to update
 * @param The key to be parsed
 * @return The action code
 */
int action_make_move(map_t *map);


/**
 * Prompt the user to press a key to continue
 * @param The message to display
 */
void action_prompt();

#endif /* end of include guard: ACTION_H_D9AS6ZWN */
