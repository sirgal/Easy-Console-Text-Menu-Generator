#include "ectmg_utils.h"

// MACHINE-GENERATED FILE, DO NOT CHANGE
ECTMG_menu_t ECTMG_my_menu_instance[12];
ECTMG_menu_entry_t ECTMG_my_menu_all_entries[17];

#define ECTMG_my_menu_welcome_string_0 "Hello! Welcome to my test menu.\n"
#define ECTMG_my_menu_welcome_string_1 "There shall be one submenu and one function call.\n"
#define ECTMG_my_menu_welcome_string_2 "You are going deeper and deeper.\n"
#define ECTMG_my_menu_welcome_string_3 "Here they are.\n{\n:\n[\n}\n"
#define ECTMG_my_menu_welcome_string_4 "Line 1.\nLine 2.\nLine 3.\n"
#define ECTMG_my_menu_welcome_string_5 ""
#define ECTMG_my_menu_welcome_string_6 "You're at 1st level.\n"
#define ECTMG_my_menu_welcome_string_7 "You're at 2nd level.\n"
#define ECTMG_my_menu_welcome_string_8 "You're at 3rd level.\n"
#define ECTMG_my_menu_welcome_string_9 "You're at 4th level.\n"
#define ECTMG_my_menu_welcome_string_10 "You're at 5th level.\n"
#define ECTMG_my_menu_welcome_string_11 "You are the winner. Go back now.\n"

char* ECTMG_my_menu_welcome_strings[] = {
    ECTMG_my_menu_welcome_string_0,
    ECTMG_my_menu_welcome_string_1,
    ECTMG_my_menu_welcome_string_2,
    ECTMG_my_menu_welcome_string_3,
    ECTMG_my_menu_welcome_string_4,
    ECTMG_my_menu_welcome_string_5,
    ECTMG_my_menu_welcome_string_6,
    ECTMG_my_menu_welcome_string_7,
    ECTMG_my_menu_welcome_string_8,
    ECTMG_my_menu_welcome_string_9,
    ECTMG_my_menu_welcome_string_10,
    ECTMG_my_menu_welcome_string_11
};

#define ECTMG_my_menu_entry_string_0 "Call the first function \n"
#define ECTMG_my_menu_entry_string_1 "Go to the tests\n"
#define ECTMG_my_menu_entry_string_2 "Submenu\n"
#define ECTMG_my_menu_entry_string_3 "Escaped character test\n"
#define ECTMG_my_menu_entry_string_4 "Call the second function \n"
#define ECTMG_my_menu_entry_string_5 "Multi-line welcome text there\n"
#define ECTMG_my_menu_entry_string_6 "Call the third function \n"
#define ECTMG_my_menu_entry_string_7 "Call the fourth function \n"
#define ECTMG_my_menu_entry_string_8 "Third function, too \n"
#define ECTMG_my_menu_entry_string_9 "Empty menu with no description here\n"
#define ECTMG_my_menu_entry_string_10 "Call the function number 5 \n"
#define ECTMG_my_menu_entry_string_11 "Go to the depths\n"
#define ECTMG_my_menu_entry_string_12 "Go deeper\n"
#define ECTMG_my_menu_entry_string_13 "Go deeper\n"
#define ECTMG_my_menu_entry_string_14 "We have to go deeper\n"
#define ECTMG_my_menu_entry_string_15 "Go deeper\n"
#define ECTMG_my_menu_entry_string_16 "End of the tunnel\n"

char* ECTMG_my_menu_entry_strings[] = {
    ECTMG_my_menu_entry_string_0,
    ECTMG_my_menu_entry_string_1,
    ECTMG_my_menu_entry_string_2,
    ECTMG_my_menu_entry_string_3,
    ECTMG_my_menu_entry_string_4,
    ECTMG_my_menu_entry_string_5,
    ECTMG_my_menu_entry_string_6,
    ECTMG_my_menu_entry_string_7,
    ECTMG_my_menu_entry_string_8,
    ECTMG_my_menu_entry_string_9,
    ECTMG_my_menu_entry_string_10,
    ECTMG_my_menu_entry_string_11,
    ECTMG_my_menu_entry_string_12,
    ECTMG_my_menu_entry_string_13,
    ECTMG_my_menu_entry_string_14,
    ECTMG_my_menu_entry_string_15,
    ECTMG_my_menu_entry_string_16
};

ECTMG_menu_entry_t* ECTMG_my_menu_entry_0[4] = {&ECTMG_my_menu_all_entries[0], &ECTMG_my_menu_all_entries[1], &ECTMG_my_menu_all_entries[11], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_1[3] = {&ECTMG_my_menu_all_entries[2], &ECTMG_my_menu_all_entries[10], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_2[4] = {&ECTMG_my_menu_all_entries[3], &ECTMG_my_menu_all_entries[5], &ECTMG_my_menu_all_entries[9], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_3[2] = {&ECTMG_my_menu_all_entries[4], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_4[4] = {&ECTMG_my_menu_all_entries[6], &ECTMG_my_menu_all_entries[7], &ECTMG_my_menu_all_entries[8], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_5[1] = {NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_6[2] = {&ECTMG_my_menu_all_entries[12], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_7[2] = {&ECTMG_my_menu_all_entries[13], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_8[2] = {&ECTMG_my_menu_all_entries[14], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_9[2] = {&ECTMG_my_menu_all_entries[15], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_10[2] = {&ECTMG_my_menu_all_entries[16], NULL};
ECTMG_menu_entry_t* ECTMG_my_menu_entry_11[1] = {NULL};

ECTMG_menu_entry_t** ECTMG_my_menu_menu_entries[] = {
    ECTMG_my_menu_entry_0,
    ECTMG_my_menu_entry_1,
    ECTMG_my_menu_entry_2,
    ECTMG_my_menu_entry_3,
    ECTMG_my_menu_entry_4,
    ECTMG_my_menu_entry_5,
    ECTMG_my_menu_entry_6,
    ECTMG_my_menu_entry_7,
    ECTMG_my_menu_entry_8,
    ECTMG_my_menu_entry_9,
    ECTMG_my_menu_entry_10,
    ECTMG_my_menu_entry_11
};

ECTMG_menu_t* ECTMG_initialize_my_menu() {
    const ECTMG_handler handlers[17] = {function_1, NULL, NULL, NULL, function_2, NULL, function_3, function_4, function_3, NULL, function_5, NULL, NULL, NULL, NULL, NULL, NULL};
    const int root_menu_ptrs[17] = {0, 0, 1, 2, 3, 2, 4, 4, 4, 2, 1, 0, 6, 7, 8, 9, 10};
    
    int menu_ptr = 1;
    
    for( int i = 0; i < 12; i++ ) {
        ECTMG_my_menu_instance[i].entries = ECTMG_my_menu_menu_entries[i];
        ECTMG_my_menu_instance[i].welcome_string = ECTMG_my_menu_welcome_strings[i];
    }
    
    for( int i = 0; i < 17; i++ ) {
        ECTMG_my_menu_all_entries[i].string = ECTMG_my_menu_entry_strings[i];
        if( handlers[i] == NULL ) {
            ECTMG_my_menu_instance[menu_ptr].prev_menu = &ECTMG_my_menu_instance[root_menu_ptrs[i]];
            ECTMG_my_menu_all_entries[i].next_menu = &ECTMG_my_menu_instance[menu_ptr++];
            ECTMG_my_menu_all_entries[i].handler = NULL;
        }
        else {
            ECTMG_my_menu_all_entries[i].next_menu = NULL;
            ECTMG_my_menu_all_entries[i].handler = handlers[i];
        }
    }
    
    ECTMG_my_menu_instance[0].prev_menu = NULL;
    return &ECTMG_my_menu_instance[0];
}
