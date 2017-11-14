#ifndef DATATYPES_H_PH0MEKHP
#define DATATYPES_H_PH0MEKHP


/**
 * A type to store boolean values:
 * B_TRUE and B_FALSE
 */
typedef enum { B_TRUE, B_FALSE } boolean;


/**
 * Enum to store the number of items in the menu
 */
enum menu_item {
    MENU_NEW_GAME,
    MENU_HELP,
    MENU_QUIT,
    MENU_SIZE
};

/**
 * Define the input key type
 */
typedef int input_key_t;

#endif /* end of include guard: DATATYPES_H_PH0MEKHP */
