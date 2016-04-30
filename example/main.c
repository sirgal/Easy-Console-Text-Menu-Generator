#include <stdio.h>
#include "ectmg_utils.h"
#include "handler_functions.h"
#include "my_menu.h"

int main()
{
    ECTMG_menu_t* start = ECTMG_initialize_my_menu();
    ECTMG_start( start );
	return 0;
}
