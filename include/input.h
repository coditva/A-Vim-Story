#ifndef INPUT_H_D4GRHNZB
#define INPUT_H_D4GRHNZB

/**
 * Initialize and configure the input
 */
boolean input_init();

/**
 * Wait for a key press and return it
 * @return The key pressed
 */
input_key_t input_get_key();

#endif /* end of include guard: INPUT_H_D4GRHNZB */
