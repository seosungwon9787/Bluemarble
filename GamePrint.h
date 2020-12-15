#include "GamePlay.h"
#include <iostream>
#include <locale.h>
#include <ncursesw/curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
#define BRIGHT_GREEN 1
#define GREEN 2
#define BRIGHT_BLUE 3
#define BLUE 4
#define Magenta 5
#define BRIGHT_Magenta 6
#define RED 7
#define BRIGHT_RED 8
#define YELLOW 9
#define BRIGHT_WHITE 10
#define INTERFACE 11
using namespace std;

void printtext(int startx, int starty, int endx, int endy, int p1_p, int p2_p);

void printline(int startx, int starty, int endx, int endy);

void printgame(int startx, int starty, int endx, int endy, int p1_p, int p2_p);

void printready(int startx, int starty, int endx, int endy, string name);

void printresult(int startx, int starty, int endx, int endy, int dice1,
                 int dice2);

void printstatus(int startx, int endx, int endy, int money, string name,
                 vector<string> Item);

void printrolldice(int startx, int starty, int endx, int endy, int dice1,
                   int dice2);
void printbuy(int startx, int starty, int endx, int endy, int turn,
              int building, int cal1, int cal2, int cal3, int cal4);
void printchoose(int startx, int starty, int endx, int endy, int name);
