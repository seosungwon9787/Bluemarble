#include <curses.h>
#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include <ncursesw/curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

typedef struct GameStart {
    long pid;
    bool start;
} Start;

typedef struct sendP {
    long pid;
    int position;
    int money2;
    int money1;
    int Onitem;
    int who_rand[32];
    int building[32];
    int fee[32];
    int isover;
} sendP;
class GamePlayer {
  public:
    GamePlayer(string Name, int Money);
    ~GamePlayer();
    void RandomDice();
    void move();
    bool DiceDouble();
    string Name() { return this->name; }
    int Money() { return this->money; }
    void MoneyDcrease(int num) { this->money -= num; }
    void MoneyIcrease(int num) { this->money += num; }
    int Position() { return this->position; }
    void PositionMove(int n) { this->position += n; }
    vector<int> Dice() { return this->dice; }
    int hasitem(int i) { return this->Onitem += i; }
    int Item() { return this->Onitem; }
    int Dice1() { return this->dice[0]; }
    int Dice2() { return this->dice[1]; }
    int Turn() { return this->turn; }
    void setMoney(int num) { this->money = num; }
    void setposition(int num) { this->position = num; }
    int getitem() { return this->Onitem; }
    void setitem(int num) { this->Onitem = num; }

  private:
    string name;
    int money;
    int position;
    vector<int> dice;
    int Onitem = 0;
    int turn;
};
struct Land {
    int rand;
    int buila;
    int building;
    int hotel;
    int randmark;
    int pass1;
    int pass2;
    int pass3;
    int pass4;
    int pass5;
};
void SettingGame(Land (&Gamestart)[32]);
