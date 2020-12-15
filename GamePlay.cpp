#include "GamePlay.h"
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
GamePlayer::GamePlayer(string Name, int Money) {
    this->name = Name;
    this->money = Money;
    this->position = 0;
    this->turn = 0;
}
GamePlayer::~GamePlayer() { delete[] & dice; }
void GamePlayer::RandomDice() {
    srand(time(NULL));
    int dice_1 = (rand() % 6) + 1;
    int dice_2 = (rand() % 6) + 1;
    this->dice.push_back(dice_1);
    this->dice.push_back(dice_2);
}

void GamePlayer::move() {
    int dice1 = dice[0];
    int dice2 = dice[1];
    for (int i = 0; i < dice1; i++) {
        if (this->position == 31) {
            this->position = 0;
            this->turn += 1;
            this->money += 300000;
        } else {
            this->position += 1;
        }
    }
    for (int i = 0; i < dice2; i++) {
        if (this->position == 31) {
            this->position = 0;
            this->turn += 1;
            this->money += 300000;
        } else {
            this->position += 1;
        }
    }
    this->dice.clear();
}

bool GamePlayer::DiceDouble() {
    if (dice[0] == dice[1]) {
        return true;
    }
    return false;
}

void SettingGame(Land (&Gamestart)[32]) {
    Gamestart[0].rand = 0;
    Gamestart[1].rand = 20000;
    Gamestart[2].rand = 0;
    Gamestart[3].rand = 26000;
    Gamestart[4].rand = 100000;
    Gamestart[5].rand = 48000;
    Gamestart[6].rand = 48000;
    Gamestart[7].rand = 54000;
    Gamestart[8].rand = 0;
    Gamestart[9].rand = 100000;
    Gamestart[10].rand = 72000;
    Gamestart[11].rand = 72000;
    Gamestart[12].rand = 0;
    Gamestart[13].rand = 94000;
    Gamestart[14].rand = 100000;
    Gamestart[15].rand = 100000;
    Gamestart[16].rand = 0;
    Gamestart[17].rand = 118000;
    Gamestart[18].rand = 100000;
    Gamestart[19].rand = 124000;
    Gamestart[20].rand = 0;
    Gamestart[21].rand = 140000;
    Gamestart[22].rand = 146000;
    Gamestart[23].rand = 146000;
    Gamestart[24].rand = 0;
    Gamestart[25].rand = 100000;
    Gamestart[26].rand = 164000;
    Gamestart[27].rand = 170000;
    Gamestart[28].rand = 0;
    Gamestart[29].rand = 192000;
    Gamestart[30].rand = 0;
    Gamestart[31].rand = 200000;
    int num1 = 10000;
    int num2 = 30000;
    int num3 = 50000;
    for (int i = 0; i < 32; i++) {
        if (i == 4 || i == 9 || i == 14 || i == 18 || i == 25) {
            Gamestart[i].buila = 0;
            Gamestart[i].building = 0;
            Gamestart[i].hotel = 0;
            Gamestart[i].randmark = 0;
            Gamestart[i].pass1 = 60000;
            Gamestart[i].pass2 = 0;
            Gamestart[i].pass3 = 0;
            Gamestart[i].pass4 = 0;
            Gamestart[i].pass5 = 0;
            continue;
        } else if (i == 0 || i == 2 || i == 8 || i == 12 || i == 16 ||
                   i == 20 || i == 24 || i == 28 || i == 30) {
            Gamestart[i].buila = 0;
            Gamestart[i].building = 0;
            Gamestart[i].hotel = 0;
            Gamestart[i].randmark = 0;
            Gamestart[i].pass1 = 0;
            Gamestart[i].pass2 = 0;
            Gamestart[i].pass3 = 0;
            Gamestart[i].pass4 = 0;
            Gamestart[i].pass5 = 0;
            continue;
        } else if (i <= 3) {
            Gamestart[i].buila = num1;
            Gamestart[i].building = num2;
            Gamestart[i].hotel = num3;
            Gamestart[i].randmark = num3;
            Gamestart[i].pass1 = 2000;
            Gamestart[i].pass2 = 10000;
            Gamestart[i].pass3 = 32000;
            Gamestart[i].pass4 = 92000;
            Gamestart[i].pass5 = 342000;
        } else if (i <= 7) {
            Gamestart[i].buila = num1 * 2;
            Gamestart[i].building = num2 * 2;
            Gamestart[i].hotel = num3 * 2;
            Gamestart[i].randmark = num3 * 2;
            Gamestart[i].pass1 = 8000;
            Gamestart[i].pass2 = 28000;
            Gamestart[i].pass3 = 76000;
            Gamestart[i].pass4 = 200000;
            Gamestart[i].pass5 = 650000;
        } else if (i <= 11) {
            Gamestart[i].buila = num1 * 3;
            Gamestart[i].building = num2 * 3;
            Gamestart[i].hotel = num3 * 3;
            Gamestart[i].randmark = num3 * 3;
            Gamestart[i].pass1 = 14000;
            Gamestart[i].pass2 = 46000;
            Gamestart[i].pass3 = 130000;
            Gamestart[i].pass4 = 350000;
            Gamestart[i].pass5 = 950000;
        } else if (i <= 15) {
            Gamestart[i].buila = num1 * 4;
            Gamestart[i].building = num2 * 4;
            Gamestart[i].hotel = num3 * 4;
            Gamestart[i].randmark = num3 * 4;
            Gamestart[i].pass1 = 24000;
            Gamestart[i].pass2 = 72000;
            Gamestart[i].pass3 = 190000;
            Gamestart[i].pass4 = 470000;
            Gamestart[i].pass5 = 1170000;
        } else if (i <= 19) {
            Gamestart[i].buila = num1 * 5;
            Gamestart[i].building = num2 * 5;
            Gamestart[i].hotel = num3 * 5;
            Gamestart[i].randmark = num3 * 5;
            Gamestart[i].pass1 = 34000;
            Gamestart[i].pass2 = 108000;
            Gamestart[i].pass3 = 280000;
            Gamestart[i].pass4 = 670000;
            Gamestart[i].pass5 = 1420000;
        } else if (i <= 23) {
            Gamestart[i].buila = num1 * 6;
            Gamestart[i].building = num2 * 6;
            Gamestart[i].hotel = num3 * 6;
            Gamestart[i].randmark = num3 * 6;
            Gamestart[i].pass1 = 48000;
            Gamestart[i].pass2 = 140000;
            Gamestart[i].pass3 = 360000;
            Gamestart[i].pass4 = 830000;
            Gamestart[i].pass5 = 1580000;
        } else if (i <= 27) {
            Gamestart[i].buila = num1 * 7;
            Gamestart[i].building = num2 * 7;
            Gamestart[i].hotel = num3 * 7;
            Gamestart[i].randmark = num3 * 7;
            Gamestart[i].pass1 = 60000;
            Gamestart[i].pass2 = 190000;
            Gamestart[i].pass3 = 480000;
            Gamestart[i].pass4 = 1100000;
            Gamestart[i].pass5 = 1800000;
        } else if (i <= 31) {
            Gamestart[i].buila = num1 * 8;
            Gamestart[i].building = num2 * 8;
            Gamestart[i].hotel = num3 * 8;
            Gamestart[i].randmark = num3 * 8;
            Gamestart[i].pass1 = 80000;
            Gamestart[i].pass2 = 240000;
            Gamestart[i].pass3 = 580000;
            Gamestart[i].pass4 = 1280000;
            Gamestart[i].pass5 = 1880000;
        }
    }
}
