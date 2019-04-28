#include <criterion/criterion.h>
#include "datatypes.h"
#include "interface.h"

void setup(void)
{
    interface_init();
}

void teardown(void)
{
    interface_destroy();
}

Test(interface, init, .init = setup, .fini = teardown) {
    interface_display_clear();
    interface_display_menu(1);
    cr_expect(1, "some test");
}
