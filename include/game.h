#ifndef GAME_H_VAPGITSI
#define GAME_H_VAPGITSI

/**
 * Intialize the game
 * @return B_TRUE if success, B_FALSE otherwise
 */
boolean game_init();


/**
 * Create, play and destroy the game
 * @return The status for the game
 */
int game_play();

#endif /* end of include guard: GAME_H_VAPGITSI */
