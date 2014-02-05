#ifndef TEXT_MENU
#define TEXT_MENU

#include <stdio.h>
#include <stdlib.h>

struct MENU_menu_type; 
struct MENU_menu_entry_type;
typedef void( *MENU_handler )();

// user interface
void MENU_start( struct MENU_menu_type *start );
void MENU_deallocate( struct MENU_menu_type *start );

// internal
int MENU_getChoice();
void MENU_entryDeallocate( struct MENU_menu_type *start );
int MENU_printEntries( struct MENU_menu_type *menu );

typedef struct MENU_menu_type
{
	char *welcome_string;
	struct MENU_menu_type *prev_menu;
	struct MENU_menu_entry_type **entries;
} MENU_menu_type;

typedef struct MENU_menu_entry_type
{
	char *string;
	struct MENU_menu_type *next_menu;
	MENU_handler handler;
} MENU_menu_entry_type;

int MENU_getChoice()
{
	int choice;
	scanf( "%d", &choice );

	return choice;
}

void MENU_entryDeallocate( MENU_menu_type *start )
{
	MENU_menu_entry_type *entry = start->entries[0];

	for( int i = 0;; i++ ) {
		entry = start->entries[i];

		if( entry == NULL )
			break;

		if( entry->next_menu != NULL )
			MENU_entryDeallocate( entry->next_menu );

		free( entry->string );
	}

	free( start->welcome_string );
	free( start->entries );
}

void MENU_deallocate( MENU_menu_type *start )
{
	MENU_menu_entry_type *delete_later = start->entries[0];
	MENU_entryDeallocate( start );

	free( delete_later );
	free( start );
}

int MENU_printEntries( MENU_menu_type *menu )
{
	int i;

	printf( "\n%s", menu->welcome_string );

	for( i = 1; menu->entries[i-1] != NULL; i++ ) {
		printf( "%d) %s", i, menu->entries[i-1]->string );
	}

	if( menu->prev_menu != NULL )
		printf( "%d) Back\n", i );
	else 
		printf( "%d) Exit\n", i );

	return i;
}

void MENU_start( MENU_menu_type *start )
{
	MENU_menu_type *current_menu = start;
	int element_count, choice;

	while( current_menu != NULL ) {
		element_count = MENU_printEntries( current_menu ) - 1;
		choice = MENU_getChoice() - 1;

		if( choice >= 0 && choice < element_count ) {
			if( current_menu->entries[choice]->handler != NULL )
				current_menu->entries[choice]->handler();
			else
				current_menu = current_menu->entries[choice]->next_menu;
		} else if( choice == element_count ) {
			current_menu = current_menu->prev_menu;
		} else {
			printf( "Please, try again.\n" );
		}
	}
}

#endif
