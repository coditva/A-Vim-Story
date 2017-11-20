#include <criterion/criterion.h>
#include "datatypes.h"
#include "key.h"

Test(key, lock_all) {
    key_lock_all();

    cr_expect(!key_unlocked('a'), "Key should be locked when locked");
}
