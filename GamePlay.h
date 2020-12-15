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
    vector<int> Dice() { return this->dice; }
    vector<string> My_item() { return this->my_item; }
    int Dice1() { return this->dice[0]; }
    int Dice2() { return this->dice[1]; }
    int Turn() { return this->turn; }

  private:
    string name;
    int money;
    int position;
    vector<int> dice;
    vector<string> my_item;
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
