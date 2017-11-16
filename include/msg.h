#ifndef MSG_H_TQLNM5HF
#define MSG_H_TQLNM5HF


/**
 * Initialize the messages
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean msg_init();


/**
 * Destroy the initialized messages
 * @return boolean B_TRUE if success, B_FALSE otherwise
 */
boolean msg_destroy();


/**
 * Get the message for a given key
 * @param The key for which to get the message
 * @return The message for the key
 */
char * msg_get_keymsg(input_key_t);

#endif /* end of include guard: MSG_H_TQLNM5HF */
