#include <stdio.h>
#include "menu_utils.h"
#include "handler_functions.h"
#include "my_menu.h"

int main()
{
	MENU_menu_type *start = MENU_initialize_my_menu();
	MENU_start( start );
	MENU_deallocate( start );
	return 0;
}
