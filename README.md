Easy-Console-Text-Menu-Generator
================================

Python script for easy generation of text menus for further use in C programs

Features:
- Welcome messages
- Nested menus
- Handler functions
- Written in C89
- Extreme ease of use - just write down menu layout, run script, include a few headers and you're set
- Resource efficiency
- Will run on anything with printf, scanf and dynamic memory allocation
- (With some tinkering - on anything)
- Do we need more? It's a console menu, after all

Why:
  Text user interface is the most basic interface possible. 
  Sometimes you don't need more than that, sometimes it's the only interface possible.
  Nevertheless, writing it in code can be a real pain. 
  Simple menu can transform into 400 lines of nested switch cases. 
  It is hard to debug, read and change, especially when you're trying to write simple debug console for some microcontroller.

Solution:
  Design menu layout in a text file first, parse it with a script that will generate code for this layout, include generated header in a project, run generated function.
  Much easier than trying to write that in code immidiately, using 9001 switch cases.
  
Usage:
1) Design layout in a text file.

  Each menu, except the main one, starts with a label, ending with a colon
      This is a label:
      
  Menu content is located between curly braces. Each brace on its own line.
      This is a label:
      {
        Submenu:
        {
        
        }
      }
      
  Welcome message is located between the menu label and the starting curly brace.
      This is a label:
      Welcome to the menu!
      {
        Submenu:
        You have entered the submenu!
        {
        
        }
      }
  
  Function names to call are situated in square braces, after the label
      This is a label:
      Welcome to the menu!
      {
        Submenu:
        You have entered the submenu!
        {
            Call function 0 [ func0 ]
            Call function 1 [ func1 ]
            Call function 2 [ func2 ]
        }
      }
      
  To use special characters such as : { } [ ] in a label or message, escape it with \ character
  Handlers should take no arguments and return no value: void handler() {}

2) Run the script.

  First argument - input file name.
  Second argument - output file name. WARNING: FILE WILL BE OVERWRITTEN.
  Third argument - desired unique name for the menu-generating function.
  
  Script doesn't check for syntax errors, so be careful with your layout. 
  
3) Include headers.

  First, include the "menu_utils.h" to your project. It contains user functions to run and delete generated menu.
  Then, include all the generated layout headers.
  
4) Run.
  
  MENU_initialize_chosenuniquename function, located in a generated function, allocates memory and creates menu of desired layout. Returned value of type MENU_menu_type is the root of your menu.
  Pass it to MENU_start and you're done
  To free all the allocated memory, use MENU_deallocate
  
  Usage example:
  #include "menu_utils.h"
  #include "my_menu.h"

  int main()
  {
  	MENU_menu_type *menu = MENU_initialize_my_menu();
  	MENU_start( menu );
  	MENU_deallocate( menu );
  	return 0;
  }
  
