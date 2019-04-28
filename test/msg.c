#include <criterion/criterion.h>
#include "datatypes.h"
#include "msg.h"

Test(msg, msg_get_keymsg) {
    cr_expect(msg_get_keymsg(' ' - 1) == NULL,
            "The msg before the first key ' ' should be NULL");

    cr_expect(msg_get_keymsg(' ') != NULL,
            "The msg for the first key ' ' should be there");

    cr_expect(msg_get_keymsg(KEY_MAX_SIZE + 1) == NULL,
            "The msg after the last key should be NULL");

    cr_expect(msg_get_keymsg(KEY_MAX_SIZE) != NULL,
            "The msg for the last key should be there");
}
