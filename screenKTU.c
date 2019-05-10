/***
   *  Autorius: Eimutis Karčiauskas -- KTU IF Programų inžinerijos katedra
   *  --------------  Ekrano valdymo funkcijų rinkinys  -------------
   *  Tai mokomojo funkcijų rinkinio antraščių failas pragraminė realizacija.
   *  Pagal studijų planą analizuoti šių funkcijų programinio kodo nereikia.
   *  Tačiau besidomintys studentai tai gali atlikti savo iniciatyva.
   *
   ****************************************************************************/
#include "screenKTU.h"

int sysBackColor=BLACK, sysFontColor=GRAY;
void goRC(int row, int column){
        COORD pozicija = {column, row};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pozicija);
}
void setBackColor(int backColor) {
     sysBackColor = backColor;
     WORD wColor = ((sysBackColor & 0x0F) << 4) + (sysFontColor & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void setFontColor(int fontColor) {
     sysFontColor = fontColor;
     WORD wColor = ((sysBackColor & 0x0F) << 4) + (sysFontColor & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void setColors(int backColor, int fontColor) {
     sysBackColor = backColor;
     sysFontColor = fontColor;
     WORD wColor = ((sysBackColor & 0x0F) << 4) + (sysFontColor & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void putChar(int row, int column, char c){
    goRC(row, column);
    putchar(c);
}
void putString(int row, int column, char *string){
    goRC(row, column);
    char convert[80];
    CharToOem(string, convert);
    printf("%s", convert);
}
void paint(int row, int column, int color){
    goRC(row, column);
    setBackColor(color);
    putchar(' ');
}
void fillRect(int rowTop, int columnLeft, int countRow, int countColumn, char ch){
    int row, col;
    for(row=0; row<countRow; row++){
        goRC(rowTop+row, columnLeft);
        for(col=0; col<countColumn; col++)
            putchar(ch);
    }
}
void drawBorder1(int rowTop, int columnLeft, int countRow, int countColumn);
void drawBorder2(int rowTop, int columnLeft, int countRow, int countColumn);
void drawBorder(int rowTop, int columnLeft, int countRow, int countColumn, char ch){
    if (ch==LINE1) {drawBorder1(rowTop, columnLeft, countRow, countColumn); return; }
    if (ch==LINE2) {drawBorder2(rowTop, columnLeft, countRow, countColumn); return; }
    int row, col;
    int lastRow = rowTop+countRow-1;
    int lastColumn = columnLeft+countColumn-1;
    for(row=rowTop; row<=lastRow; row++){
        goRC(row, columnLeft); putchar(ch);
        goRC(row, lastColumn); putchar(ch);
    }
    for(col=columnLeft+1; col<lastColumn; col++){
        goRC(rowTop, col); putchar(ch);
        goRC(lastRow,col); putchar(ch);
    }
}
void setCursorForm(int visible){
    CONSOLE_CURSOR_INFO info;
    info.bVisible = (BOOL)visible;
    info.dwSize = 4;
    SetConsoleCursorInfo(GetStdHandle (STD_OUTPUT_HANDLE),&info);
}
char getRC(int row, int column){
    unsigned char symbol;
    DWORD numberRead;
    COORD pozicija = {column, row};
    ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &symbol, 1, pozicija, &numberRead);
    return (unsigned char)symbol;
}

unsigned char overL[6][40] = {
{195,197,0,215,210,0,0,199,0,0,208,0,194,0,0,0,0,0,0,195,0,211,214,0,0,199,0,0,0,0,0,0,0,192,218,0,0,0,193,0},
{180,0,180,0,0,191,182,182,183,189,0,217,0,193,0,0,197,0,0,0,215,0,0,0,0,0,0,0,0,0,0,0,0,192,218,0,0,0,0,194},
{197,197,197,215,210,194,215,215,210,208,208,193,194,193,0,0,197,0,0,197,215,208,210,208,210,215,196,215,193,0,194,0,208,193,194,210,0,197,193,194},
{0,0,0,0,191,0,0,0,184,0,0,181,0,195,197,0,0,194,0,0,0,0,213,0,209,0,209,0,216,0,0,194,0,198,0,218,0,0,180,0},
{0,0,0,0,0,181,0,0,0,190,217,0,180,0,0,197,0,193,0,0,0,212,0,207,0,0,207,0,0,193,216,0,192,0,198,0,0,0,0,195},
{0,0,0,180,180,181,181,179,181,181,180,181,180,195,197,197,0,197,0,0,195,198,198,216,216,198,216,216,216,195,216,197,197,198,198,195,197,0,180,195}
};
char charLimit = 179;
void putOverChar(int row, int column, char chType){
    char cc = chType<=2 ? 196: 179;
    unsigned char ch = getRC(row, column);
    if(chType==0 && ch==179){
    }
    if (ch>=179 && ch<=217) {
        unsigned char k = ch - charLimit;
        if(cc == overL[chType][k])
            putChar(row, column, cc);
    } else
        putChar(row, column, cc);
}
void drawLine(int rowStart, int columnStart, int count, char lineType){
    int row, col;
    if(lineType==L_HOR){
        int lastColumn = columnStart + count - 1;
        putOverChar(rowStart, columnStart, 0);
        for(col=columnStart+1; col<lastColumn; col++)
            putOverChar(rowStart, col, 2);
        putOverChar(rowStart, lastColumn , 1);
    }
    else {
        int lastRow = rowStart + count - 1;
        putOverChar(rowStart, columnStart, 3);
        for(row=rowStart+1; row<lastRow; row++)
            putOverChar(row, columnStart, 5);
        putOverChar(lastRow, columnStart, 4);
    }
}
void drawBorder1(int rowTop, int columnLeft, int countRow, int countColumn){
    int row, col;
    int lastRow = rowTop + countRow - 1;
    int lastColumn = columnLeft + countColumn - 1;
    for(row=rowTop+1; row<lastRow; row++){
        putOverChar(row, columnLeft, 5);
        putOverChar(row, lastColumn, 5);
    }
    for(col=columnLeft+1; col<lastColumn; col++){
        putOverChar(rowTop, col, 2);
        putOverChar(lastRow,col, 2);
    }
    goRC(rowTop, columnLeft); putchar(218);
    goRC(rowTop, lastColumn); putchar(191);
    goRC(lastRow,columnLeft); putchar(192);
    goRC(lastRow,lastColumn); putchar(217);
}
void drawBorder2(int rowTop, int columnLeft, int countRow, int countColumn){
    int row, col;
    int lastRow = rowTop + countRow - 1;
    int lastColumn = columnLeft + countColumn - 1;
    for(row=rowTop+1; row<lastRow; row++){
        goRC(row, columnLeft); putchar(186);
        goRC(row, lastColumn); putchar(186);
    }
    for(col=columnLeft+1; col<lastColumn; col++){
        goRC(rowTop, col); putchar(205);
        goRC(lastRow,col); putchar(205);
    }
    goRC(rowTop, columnLeft); putchar(201);
    goRC(rowTop, lastColumn); putchar(187);
    goRC(lastRow,columnLeft); putchar(200);
    goRC(lastRow,lastColumn); putchar(188);
}

