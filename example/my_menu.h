#include "menu_utils.h"

// MACHINE-GENERATED FILE, DO NOT CHANGE
MENU_menu_type* MENU_initialize_my_menu( )
{
	const int menu_sizes[12] = { 3, 2, 3, 1, 3, 0, 1, 1, 1, 1, 1, 0 };
	int entry_counters[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	const int string_lengths[12] = { 34, 51, 34, 24, 25, 1, 22, 22, 22, 22, 22, 34 };
	const int entry_name_lengths[17] = { 26, 17, 9, 24, 27, 31, 26, 27, 22, 37, 29, 18, 11, 11, 22, 11, 19 };
	const MENU_handler handlers[17] = { function_1, NULL, NULL, NULL, function_2, NULL, function_3, function_4, function_3, NULL, function_5, NULL, NULL, NULL, NULL, NULL, NULL };
	const int root_menu_ptrs[17] = { 0, 0, 1, 2, 3, 2, 4, 4, 4, 2, 1, 0, 6, 7, 8, 9, 10 };

	int menu_ptr = 1;

	MENU_menu_type *menu = (MENU_menu_type*) malloc( sizeof(MENU_menu_type) * 12 );
	MENU_menu_entry_type *entries = (MENU_menu_entry_type*) malloc( sizeof(MENU_menu_entry_type) * 17 );

	for( int i = 0; i < 12; i++ ) {
		menu[i].entries = (MENU_menu_entry_type**) malloc( sizeof(MENU_menu_entry_type*) * ( menu_sizes[i] + 1 ) );
		menu[i].welcome_string = (char*) malloc( sizeof(char) * string_lengths[i] );
		menu[i].entries[menu_sizes[i]] = NULL;
	}

	memcpy( menu[0].welcome_string, "Hello! Welcome to the test menu.\n", string_lengths[0] );
	memcpy( menu[1].welcome_string, "There shall be one submenu and one function call.\n", string_lengths[1] );
	memcpy( menu[2].welcome_string, "You are going deeper and deeper.\n", string_lengths[2] );
	memcpy( menu[3].welcome_string, "Here they are.\n{\n:\n[\n}\n", string_lengths[3] );
	memcpy( menu[4].welcome_string, "Line 1.\nLine 2.\nLine 3.\n", string_lengths[4] );
	memcpy( menu[5].welcome_string, "", string_lengths[5] );
	memcpy( menu[6].welcome_string, "You're at 1st level.\n", string_lengths[6] );
	memcpy( menu[7].welcome_string, "You're at 2nd level.\n", string_lengths[7] );
	memcpy( menu[8].welcome_string, "You're at 3rd level.\n", string_lengths[8] );
	memcpy( menu[9].welcome_string, "You're at 4th level.\n", string_lengths[9] );
	memcpy( menu[10].welcome_string, "You're at 5th level.\n", string_lengths[10] );
	memcpy( menu[11].welcome_string, "You are the winner. Go back now.\n", string_lengths[11] );

	for( int i = 0; i < 17; i++ ) {
		entries[i].string = (char*) malloc( sizeof(char) * entry_name_lengths[i] );
		menu[root_menu_ptrs[i]].entries[entry_counters[root_menu_ptrs[i]]++] = &entries[i];
		if( handlers[i] == NULL ) {
			menu[menu_ptr].prev_menu = &menu[root_menu_ptrs[i]];
			entries[i].next_menu = &menu[menu_ptr++];
			entries[i].handler = NULL;
		} else {
			entries[i].next_menu = NULL;
			entries[i].handler = handlers[i];
		}
	}

	memcpy( entries[0].string, "Call the first function \n", entry_name_lengths[0] );
	memcpy( entries[1].string, "Go to the tests\n", entry_name_lengths[1] );
	memcpy( entries[2].string, "Submenu\n", entry_name_lengths[2] );
	memcpy( entries[3].string, "Escaped character test\n", entry_name_lengths[3] );
	memcpy( entries[4].string, "Call the second function \n", entry_name_lengths[4] );
	memcpy( entries[5].string, "Multi-line welcome text there\n", entry_name_lengths[5] );
	memcpy( entries[6].string, "Call the third function \n", entry_name_lengths[6] );
	memcpy( entries[7].string, "Call the fourth function \n", entry_name_lengths[7] );
	memcpy( entries[8].string, "Third function, too \n", entry_name_lengths[8] );
	memcpy( entries[9].string, "Empty menu with no description here\n", entry_name_lengths[9] );
	memcpy( entries[10].string, "Call the function number 5 \n", entry_name_lengths[10] );
	memcpy( entries[11].string, "Go to the depths\n", entry_name_lengths[11] );
	memcpy( entries[12].string, "Go deeper\n", entry_name_lengths[12] );
	memcpy( entries[13].string, "Go deeper\n", entry_name_lengths[13] );
	memcpy( entries[14].string, "We have to go deeper\n", entry_name_lengths[14] );
	memcpy( entries[15].string, "Go deeper\n", entry_name_lengths[15] );
	memcpy( entries[16].string, "End of the tunnel\n", entry_name_lengths[16] );

	menu[0].prev_menu = NULL;
	return &menu[0];
}
