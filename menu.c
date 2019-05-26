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
    {
        f = fopen(HSCORE_FILE, "w"); // Create a high score file
        f = fopen(HSCORE_FILE, "r"); // Read it
    }

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

                    for (int k = j; k >= 0; --k)  // Removes white spaces from a name
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

        system("cls");
        do
        {
            setColors(BLACK, GREEN);
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
            setColors(BLACK, BLUE-BRIGHT);
            printf("TIP: Use arrow up key for a previuos input \n\n");       // TODO draw fancy border
            printf("Enter your name: ");       // TODO draw fancy border
            Sleep(350);             // Accidental inputs filter
            flushInputBuffer();

            setColors(BLACK, BLUE);
            fgets(name, HSCORES_NAME_LEN, stdin);   // Read input
            name[strcspn(name, "\n")] = 0;

            setCursorForm(0);

            // Repeat input if name is invalid
            if (strcspn(name, "\0") == 0 || isspace(name[0]))
            {
                system("cls");
                setColors(BLACK, RED);
                goRC(6, 0);
                printf("Your name is invalid. Please enter again");
            }
            else
            {
                break;
            }
        }
        while (true);

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

void menuOptions()
{
    static int selected = 0;
    static int map_num = 0;

    // Update
    if (input_global == KEY_UP)
        --selected;
    else if (input_global == KEY_DOWN)
        ++selected;
    selected = warpIndex(selected, 2);

    // Change speed value
    if (selected == 0) // Speed selection
    {
        if (input_global == KEY_RIGHT)
            ++snake.speed;
        else if (input_global == KEY_LEFT)
            --snake.speed;
        snake.speed = warpIndex2(snake.speed, 1, 30);
    }
    else if (selected == 1) // Map selection
    {
        if (input_global == KEY_RIGHT)
            ++map_num;
        else if (input_global == KEY_LEFT)
            --map_num;

        // Construct map filename
        char filename[15];
        sprintf(filename, "map%d.txt", map_num);

        if (!isFileExist(filename))
        {
            map_num = 0;
            strcpy(map_filename, MAP_DEFAULT);
        }
        else
        {
            strcpy(map_filename, filename);
        }
    }

    // Draw
    goRC(2, 0);
    setColors(BLACK, WHITE);
    printf("                 OPTIONS\n\n");  // TODO fancy text
    printf("     Left and Right to change value\n");

    printf("\n");
    printf("       Game Speed: %d      \n", snake.speed);
    printf("       Map       : %s      \n", map_filename);

    goRC(6 + selected, 6);
    printf("*");
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

    printf("\n\nInfo about sneks:\n");
    printf("https://www.youtube.com/watch?v=0arsPXEaIUY");
}

void drawExit()
{
    system("cls");
    setFontColor(WHITE);
    int h=21, w=66;
    drawBorder( 2,   29, h,w, LINE2);
    setColors(BLUE, RED);
    int start=3,start1=30;
    fillRect(1+start, 3+start1, 1, 4, SYM_BLANK);
    fillRect(2+start, 1+start1, 2, 2, SYM_BLANK);
    fillRect(2+start, 7+start1, 1, 2, SYM_BLANK);
    fillRect(4+start, 3+start1, 1, 2, SYM_BLANK);
    fillRect(5+start, 5+start1, 1, 2, SYM_BLANK);
    fillRect(6+start, 7+start1, 2, 2, SYM_BLANK);
    fillRect(7+start, 1+start1, 1, 2, SYM_BLANK);
    fillRect(8+start, 3+start1, 1, 4, SYM_BLANK);

    fillRect(1+start, 11+start1, 1, 8, SYM_BLANK);
    fillRect(2+start, 11+start1, 6, 2, SYM_BLANK);
    fillRect(4+start, 13+start1, 1, 4, SYM_BLANK);
    fillRect(8+start, 11+start1, 1, 8, SYM_BLANK);

    fillRect(1+start, 21+start1, 1, 8, SYM_BLANK);
    fillRect(2+start, 21+start1, 6, 2, SYM_BLANK);
    fillRect(4+start, 23+start1, 1, 4, SYM_BLANK);
    fillRect(8+start, 21+start1, 1, 8, SYM_BLANK);

    fillRect(1+start, 33+start1, 1, 2, SYM_BLANK);
    fillRect(1+start, 41+start1, 1, 2, SYM_BLANK);
    fillRect(2+start, 35+start1, 1, 2, SYM_BLANK);
    fillRect(2+start, 39+start1, 1, 2, SYM_BLANK);
    fillRect(3+start, 37+start1, 6, 2, SYM_BLANK);

    fillRect(1+start, 47+start1, 1, 4, SYM_BLANK);
    fillRect(2+start, 45+start1, 6, 2, SYM_BLANK);
    fillRect(2+start, 51+start1, 6, 2, SYM_BLANK);
    fillRect(8+start, 47+start1, 1, 4, SYM_BLANK);

    fillRect(1+start, 55+start1, 7, 2, SYM_BLANK);
    fillRect(1+start, 61+start1, 7, 2, SYM_BLANK);
    fillRect(8+start, 57+start1, 1, 4, SYM_BLANK);

    fillRect(10+start, 7+start1, 8, 2, SYM_BLANK);
    fillRect(10+start, 19+start1, 1, 4, SYM_BLANK);

    fillRect(11+start, 17+start1, 7, 2, SYM_BLANK);
    fillRect(11+start, 23+start1, 7, 2, SYM_BLANK);
    fillRect(15+start, 19+start1, 1, 4, SYM_BLANK);
    fillRect(17+start, 9+start1, 1, 6, SYM_BLANK);

    fillRect(10+start, 27+start1, 1, 10, SYM_BLANK);
    fillRect(11+start, 31+start1, 7, 2, SYM_BLANK);

    fillRect(10+start, 39+start1, 1, 8, SYM_BLANK);
    fillRect(11+start, 39+start1, 6, 2, SYM_BLANK);
    fillRect(13+start, 41+start1, 1, 4, SYM_BLANK);
    fillRect(17+start, 39+start1, 1, 8, SYM_BLANK);

    fillRect(10+start, 49+start1, 1, 6, SYM_BLANK);
    fillRect(11+start, 49+start1, 7, 2, SYM_BLANK);
    fillRect(11+start, 55+start1, 2, 2, SYM_BLANK);
    fillRect(13+start, 51+start1, 1, 4, SYM_BLANK);
    fillRect(14+start, 55+start1, 4, 2, SYM_BLANK);

    int r=12, l=3;
    int start2=16,start3=28, stulp=0;

    while(!kbhit())
    {
        paint(start2+r/2, start3+stulp, CYAN);
        paint(start2+r/2, start3+stulp+1, CYAN);
        paint(start2+r/2, start3+stulp+4, CYAN);
        paint(start2+r/2, start3+stulp+5, CYAN);
        paint(start2+r/2, start3+stulp+8, CYAN);
        paint(start2+r/2, start3+stulp+9, CYAN);
        paint(start2+r/2, start3+stulp+12, CYAN);
        paint(start2+r/2, start3+stulp+13, CYAN);
        paint(start2+r/2, start3+stulp+16, CYAN);
        paint(start2+r/2, start3+stulp+17, CYAN);
        paint(start2+r/2, start3+stulp+20, CYAN);
        paint(start2+r/2, start3+stulp+21, CYAN);
        paint(start2+r/2, start3+stulp+24, CYAN);
        paint(start2+r/2, start3+stulp+25, CYAN);
        paint(start2+r/2, start3+stulp+28, CYAN);
        paint(start2+r/2, start3+stulp+29, CYAN);
        paint(start2+r/2, start3+stulp+32, CYAN);
        paint(start2+r/2, start3+stulp+33, CYAN);
        paint(start2+r/2, start3+stulp+36, CYAN);
        paint(start2+r/2, start3+stulp+37, CYAN);
        paint(start2+r/2, start3+stulp+40, CYAN);
        paint(start2+r/2, start3+stulp+41, CYAN);
        paint(start2+r/2, start3+stulp+44, CYAN);
        paint(start2+r/2, start3+stulp+45, CYAN);
        paint(start2+r/2, start3+stulp+48, CYAN);
        paint(start2+r/2, start3+stulp+49, CYAN);
        paint(start2+r/2, start3+stulp+52, CYAN);
        paint(start2+r/2, start3+stulp+53, CYAN);
        paint(start2+r/2, start3+stulp+56, CYAN);
        paint(start2+r/2, start3+stulp+57, CYAN);
        paint(start2+r/2, start3+stulp+60, CYAN);
        paint(start2+r/2, start3+stulp+61, CYAN);
        paint(start2+r/2, start3+stulp+64, CYAN);
        paint(start2+r/2, start3+stulp+65, CYAN);
        Sleep(150);
        paint(start2+r/2, start3+stulp, BLACK);
        paint(start2+r/2, start3+stulp+1, BLACK);
        paint(start2+r/2, start3+stulp+4, BLACK);
        paint(start2+r/2, start3+stulp+5, BLACK);
        paint(start2+r/2, start3+stulp+8, BLACK);
        paint(start2+r/2, start3+stulp+9, BLACK);
        paint(start2+r/2, start3+stulp+12, BLACK);
        paint(start2+r/2, start3+stulp+13, BLACK);
        paint(start2+r/2, start3+stulp+16, BLACK);
        paint(start2+r/2, start3+stulp+17, BLACK);
        paint(start2+r/2, start3+stulp+20, BLACK);
        paint(start2+r/2, start3+stulp+21, BLACK);
        paint(start2+r/2, start3+stulp+24, BLACK);
        paint(start2+r/2, start3+stulp+25, BLACK);
        paint(start2+r/2, start3+stulp+28, BLACK);
        paint(start2+r/2, start3+stulp+29, BLACK);
        paint(start2+r/2, start3+stulp+32, BLACK);
        paint(start2+r/2, start3+stulp+33, BLACK);
        paint(start2+r/2, start3+stulp+36, BLACK);
        paint(start2+r/2, start3+stulp+37, BLACK);
        paint(start2+r/2, start3+stulp+40, BLACK);
        paint(start2+r/2, start3+stulp+41, BLACK);
        paint(start2+r/2, start3+stulp+44, BLACK);
        paint(start2+r/2, start3+stulp+45, BLACK);
        paint(start2+r/2, start3+stulp+48, BLACK);
        paint(start2+r/2, start3+stulp+49, BLACK);
        paint(start2+r/2, start3+stulp+52, BLACK);
        paint(start2+r/2, start3+stulp+53, BLACK);
        paint(start2+r/2, start3+stulp+56, BLACK);
        paint(start2+r/2, start3+stulp+57, BLACK);
        paint(start2+r/2, start3+stulp+60, BLACK);
        paint(start2+r/2, start3+stulp+61, BLACK);
        paint(start2+r/2, start3+stulp+61, BLACK);
        paint(start2+r/2, start3+stulp+64, BLACK);
        paint(start2+r/2, start3+stulp+65, BLACK);
        stulp = (stulp+1)%l;
    }
}
