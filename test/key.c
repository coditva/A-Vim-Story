#include <criterion/criterion.h>
#include "datatypes.h"
#include "key.h"

Test(key, lock_all) {
    key_unlock_all();
    key_lock_all();
    cr_expect(!key_unlocked('a'), "Key should be locked when all locked");
}

Test(key, unlock_all) {
    key_lock_all();
    key_unlock_all();
    cr_expect(key_unlocked('a'), "Key should be unlocked when all unlocked");
}
