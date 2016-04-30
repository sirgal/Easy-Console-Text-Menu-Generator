#ifndef TEXT_MENU
#define TEXT_MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ECTMG_menu_t; 
struct ECTMG_menu_entry_t;
typedef void( *ECTMG_handler )();

// user interface
void ECTMG_start( struct ECTMG_menu_t *start );

// internal
int ECTMG_getChoice();
int ECTMG_printEntries( struct ECTMG_menu_t *menu );

typedef struct ECTMG_menu_t
{
	char *welcome_string;
	struct ECTMG_menu_t *prev_menu;
	struct ECTMG_menu_entry_t **entries;
} ECTMG_menu_t;

typedef struct ECTMG_menu_entry_t
{
	char *string;
	struct ECTMG_menu_t *next_menu;
	ECTMG_handler handler;
} ECTMG_menu_entry_t;

int ECTMG_getChoice()
{
	int choice;
	scanf( "%d", &choice );
	return choice;
}

int ECTMG_printEntries( ECTMG_menu_t *menu )
{
	int i;

	printf( "\n%s", menu->welcome_string );

	for( i = 1; menu->entries[i-1] != NULL; i++ ) {
		printf( "%d) %s", i, menu->entries[i-1]->string );
	}

	if( menu->prev_menu != NULL ) {
		printf( "%d) Back\n", i );
	} else {
		printf( "%d) Exit\n", i );
	}
		
	return i;
}

void ECTMG_start( ECTMG_menu_t *start )
{
	ECTMG_menu_t *current_menu = start;
	int element_count, choice;

	while( current_menu != NULL ) {
		element_count = ECTMG_printEntries( current_menu ) - 1;
		choice = ECTMG_getChoice() - 1;

		if( choice >= 0 && choice < element_count ) {
			if( current_menu->entries[choice]->handler != NULL ) {
				current_menu->entries[choice]->handler();
			} else {
				current_menu = current_menu->entries[choice]->next_menu;
			}
		} else if( choice == element_count ) {
			current_menu = current_menu->prev_menu;
		} else {
			printf( "Please, try again.\n" );
		}
	}
}

#endif
