#include "menu.h"

char menu_main[MENU_MAIN_ELEM][MENU_ELEM_LEN] = {"Start Game", "Highscores", "Info", "Exit"}; // Do not change cuz menuSelect()
int menu_selected = 0;

void initMenu()
{
    menu_selected = 0;
    drawMenu();
}

void updateMenu()
{
    // Make manu interactable with selectable buttons
    char c = getKeyInput();
    if (c == KEY_UP)
        menu_selected = warpIndex(--menu_selected, MENU_MAIN_ELEM);
    else if (c == KEY_DOWN)
        menu_selected = warpIndex(++menu_selected, MENU_MAIN_ELEM);
    else if (c == KEY_SELECT)
        menuSelect();
}

void drawMenu()
{
    setColors(BLACK, WHITE);
    for (int i = 0; i < MENU_MAIN_ELEM; ++i)
    {
        goRC(MENU_OFFY + i, MENU_OFFX);
        if (i == menu_selected)
            putchar('*');
        else
            putchar(' ');

        printf("%s", menu_main[i]);
    }
}

void menuSelect()
{
    switch (menu_selected)
    {
    case 0:
        state_cur = STATE_GAME;
        break;
    case 1:
        state_cur = STATE_HIGHSCORES;
        break;
    case 2:
        state_cur = STATE_INFO;
        break;
    case 3:
        state_cur = STATE_EXIT;
        break;
    }
}

void drawHighscores()
{
    system("cls");
    printf("GG 999\n");
    printf("GG 998\n");
}

void drawInfo()
{
    system("cls");
    printf("Made by TNT\n");
    printf("Rainbow Snake\n");
}

