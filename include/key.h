#ifndef KEY_H_PTVHEK7H
#define KEY_H_PTVHEK7H

/**
 * Check if a key is unlocked in the game
 * @param The key to check
 * @return B_TRUE if unlocked, B_FALSE otherwise
 */
boolean key_unlocked(input_key_t);


/**
 * Unlock the given key
 * @param The key to unlock
 */
void key_unlock(input_key_t);


/**
 * Lock the given key
 * @param The key to lock
 */
void key_lock(input_key_t);


#endif /* end of include guard: KEY_H_PTVHEK7H */
