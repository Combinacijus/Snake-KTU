#include "menu.h"

// Adjust menuSelect() and MENU_MAIN_ELEM if changed
char menu_main[MENU_MAIN_ELEM][MENU_ELEM_LEN] =
    {"Start Game", "Highscore", "Options", "Info", "Exit"};
int menu_selected = 0;

void initMenu()
{
    drawMenu();
}

void updateMenu()
{
    // Make manu interactable with selectable buttons
    if (input_global == KEY_UP)
        menu_selected = warpIndex(--menu_selected, MENU_MAIN_ELEM);
    else if (input_global == KEY_DOWN)
        menu_selected = warpIndex(++menu_selected, MENU_MAIN_ELEM);
    else if (input_global == KEY_SELECT)
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
        state_cur = STATE_OPTIONS;
        break;
    case 3:
        state_cur = STATE_INFO;
        break;
    case 4:
        state_cur = STATE_EXIT;
        break;
    }
}

void saveHighscores()
{
    FILE *f;
    f = fopen(HSCORE_FILE, "w");

    if (!f)
        printf("HSCORES FILE NOT FOUND\n");

    for (int i = 0; i < HSCORES_NUM; ++i)
        fprintf(f, "%s %d\n", hscores[i].name, hscores[i].score);

    fclose(f);
}

void loadHighscores()
{
    for (int i = 0; i < HSCORES_NUM; ++i)   // Clear highscores
    {
        strcpy(hscores[i].name, "Noob");
        hscores[i].score = 0;
    }

    FILE *f;
    f = fopen(HSCORE_FILE, "r");

    if (!f)
        printf("HSCORES FILE NOT FOUND\n");

    for (int i = 0; i < HSCORES_NUM; ++i)   // Each line
    {
        int len = HSCORES_NAME_LEN + 20;
        char tmp[HSCORES_NAME_LEN + 20];

        if (!feof(f))
        {
            fgets(tmp, len, f);  // Reads all line to tmp
            if (isspace(tmp[0]))
            {
                --i;
                continue;
            }

            for (int j = strcspn(tmp, "\n") - 1; j >= 0; --j)  // Iterate back from \n
            {
                if (!isdigit(tmp[j]))  // Number start
                {
                    char tmp2[20];  // To store number in a string
                    strcpy(tmp2, &tmp[j]);  // Cut out number part
                    hscores[i].score = atoi(tmp2); // Extract number

                    for (int k = j; k >= 0; --k)  // Removes white spaces from name
                    {
                        if (isalpha(tmp[k]) || isdigit(tmp[k]))
                        {
                            strncpy(hscores[i].name, tmp, k + 1); // Extract name
                            hscores[i].name[k + 1] = '\0';
                            break;
                        }
                    }
                    break;
                }
            }
        }

//        if (feof(f))    // If file is empty
//        {
//            strcpy(hscores[i].name, "Noob");
//            hscores[i].score = 0;
//        }
    }

    fclose(f);
}

bool updateHighscores()
{
    bool is_updated = false;
    char name[HSCORES_NAME_LEN] = NONAME;
    int place_ind = 0;    // Hscore place index from 0

    loadHighscores();

    if (score > hscores[HSCORES_NUM - 1].score) // If gets in highcores
    {
        is_updated = true;
        // Find player's place
        for (int i = 0; i < HSCORES_NUM; ++i)
        {
            if (score > hscores[i].score)
            {
                place_ind = i;
                break;
            }
        }

        do
        {
            system("cls");
            setColors(BLACK, WHITE);
            goRC(0, 0);
            printf("Congratulation! You are ");
            if (place_ind == 0)
                printf("1st");
            else if (place_ind == 1)
                printf("2nd");
            else if (place_ind == 2)
                printf("3rd");
            else
                printf("%dth", place_ind + 1);
            printf("!\n");
            printf("Your score is: %d\n", score);

            // Ask for name
            setCursorForm(1);
            printf("Enter your name: ");               // TODO draw fancy border
            fgets(name, HSCORES_NAME_LEN, stdin);
            name[strcspn(name, "\n")] = 0;

            setCursorForm(0);

            // Repeat input if name is invalid
        } while (strcspn(name, "\0") == 0 || isspace(name[0]));

        for (int i = HSCORES_NUM - 2; i >= place_ind; --i) // Push scores back
        {
            hscores[i + 1].score = hscores[i].score;
            strcpy(hscores[i + 1].name, hscores[i].name);
        }

        // Push to that place
        hscores[place_ind].score = score;
        strcpy(hscores[place_ind].name, name);
    }

    return is_updated;
}

void drawHighscores()
{
    system("cls");
    setColors(BLACK, WHITE);
    printf("------------\n"); // TODO draw fancy table
    printf("|HIGHSCORES|\n");
    printf("------------\n");
    for (int i = 0; i < HSCORES_NUM; ++i)
        printf("%2d. %s %d\n", i + 1, hscores[i].name, hscores[i].score);
}

void drawInfo()
{
    system("cls");

    setColors(BLACK, WHITE);
    printf("INFO\n\n");

    setColors(BLACK, GREEN);
    printf("Rainbow Snake\n");

    setColors(BLACK, RED);
    printf("Made by TNT\n");
    printf("    Gintaras Grebliunas\n");
    printf("    Augustas Venclovas\n");
    printf("    Modestas Pustelninkas\n");
    printf("    Tadas Skeltys\n");

    setColors(BLACK, BLUE);
    printf("\n");
    printf("Controls: WASD or Arrow keys\n");
    printf("Interactions: ESC and Enter\n");

    setColors(BLACK, YELLOW);
    printf("\n");
    printf("Info: You can change snake's speed in options\n");
    printf("Info: More speed gives more points on special food\n");
}

void drawExit()
{
    system("cls");
    goRC(10, 50);
    setColors(GREEN, WHITE);
    printf("Thanks for playing!"); // TODO fancy goodbye screen
    setColors(BLACK, WHITE);
    goRC(15, 10);
}

