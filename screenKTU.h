/***
   *  Autorius: Eimutis Karèiauskas -- KTU IF Programø inþinerijos katedra
   *  --------------  Ekrano valdymo funkcijø rinkinys -------------
   *  Tai mokomojo funkcijø rinkinio antraðèiø (h) failas.
   *  Funkcijø prasmë aiðkinama atskirame apraðyme.
   *
   ****************************************************************************/
#pragma once
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

// apibrëþiame spalvø kodus, suderintus su Microsoft þymëjimais
#define BLACK 0
#define GRAY 7
#define GRAY_LIGHT 7
#define GRAY_DARK 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BRIGHT 8

#define L_HOR 1
#define L_VER 2
#define LINE1 3
#define LINE2 4

#define SYM_BLANK ' '
#define SYM_FULL 219
#define SYM_CENTER 254

void goRC(int row, int column);
void putChar(int row, int column, char c);
void putChar2(int row, int column, char c);
void putString(int row, int column, char *string);

void setBackColor(int backColor);
void setFontColor(int fontColor);
void setColors(int backColor, int fontColor);
void paint(int row, int column, int color);

void fillRect(int rowTop, int columnLeft, int countRow, int countColumn, char ch);
void drawBorder(int rowTop, int columnLeft, int countRow, int countColumn, char ch);
void drawLine(int rowStart, int columnStart, int count, char lineType);

void setCursorForm(int visible);
char getRC(int row, int column);

