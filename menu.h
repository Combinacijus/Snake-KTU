#pragma once
#include "screenKTU.h"
#include "globals.h"

#define MENU_MAIN_ELEM 4    // Main menu number of elements
#define MENU_ELEM_LEN 20    // Element max length
#define MENU_OFFX 3         // Ofsset from the left
#define MENU_OFFY 4         // Ofsset from the topextern char menu_main[][];

extern char menu_main[MENU_MAIN_ELEM][MENU_ELEM_LEN];
extern int menu_selected;


void initMenu();   // TODO
void updateMenu(); // TODO
void drawMenu();   // TODO
void menuSelect();
void drawHighscores();
void drawInfo();
