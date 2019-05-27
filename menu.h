#pragma once
#include "screenKTU.h"
#include "globals.h"
#include <ctype.h>

#define MENU_MAIN_ELEM 5    // Main menu number of elements
#define MENU_ELEM_LEN 20    // Element max length
#define MENU_OFFX 53         // Offset from the left
#define MENU_OFFY 12         // Offset from the top

extern char menu_main[MENU_MAIN_ELEM][MENU_ELEM_LEN];
extern int menu_selected;


void initMenu();
void updateMenu();
void drawMenu();
void menuSelect();
void saveHighscores();
void loadHighscores();
bool updateHighscores();    // Returns true if scores updated
void drawHighscores();
void menuOptions();
void drawInfo();
void drawExit();
