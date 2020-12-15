#include "GamePrint.h"
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

int main() {
    setlocale(LC_CTYPE, "ko_KR.utf-8");
    initscr();
    start_color();
    init_pair(BRIGHT_GREEN, 10, 0);
    init_pair(GREEN, 2, 0);
    init_pair(BRIGHT_BLUE, 12, 0);
    init_pair(BLUE, 4, 0);
    init_pair(Magenta, 5, 0);
    init_pair(BRIGHT_Magenta, 13, 0);
    init_pair(RED, 1, 0);
    init_pair(BRIGHT_RED, 9, 0);
    init_pair(YELLOW, 3, 0);
    init_pair(BRIGHT_WHITE, 15, 0);
    init_pair(INTERFACE, 6, 0);
    int startx = 0;
    int starty = 0;
    int endx = 90;
    int endy = 27;
    string map_name[32] = {
        "출발점",   "강릉",         "아이템", "춘천",       "북한산", "경주",
        "안동",     "천안",         "감옥",   "서울대공원", "인천",   "대전",
        "아이템",   "청주",         "설악산", "세종",       "엑스포", "여수",
        "지리산",   "제주",         "아이템", "포항",       "울산",   "대구",
        "기차여행", "어린이대공원", "전주",   "광주",       "아이템", "부산",
        "세금",     "서울"};
    int who_rand[32] = {-1, 0, -1, 0, 0,  0, 0, 0, -1, 0, 0, 0, -1, 0, 0,  0,
                        -1, 0, 0,  0, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0};
    int building[32] = {
        0,
    };
    int fee[32] = {
        0,
    };
    string item = "반값할인";
    Land Gamestart[32];
    SettingGame(Gamestart);
    GamePlayer player1("player1", 2000000);
    GamePlayer player2("player2", 2000000);
    int turn = 0;
    while (1) {
        if (turn == 0) {
            curs_set(0);
            noecho();
            printgame(startx, starty, endx, endy, player1.Position(),
                      player2.Position());
            printready(startx, starty, endx, endy, player1.Name());
            printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                        player1.Name(), player1.My_item());
            printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                        player2.Name(), player2.My_item());
            char num = getch();
            if (num == 'a') {
                player1.RandomDice();
                printrolldice(startx, starty, endx, endy, player1.Dice1(),
                              player1.Dice2());
                printresult(startx, starty, endx, endy, player1.Dice1(),
                            player1.Dice2());
                sleep(1);
                player1.move();
                printgame(startx, starty, endx, endy, player1.Position(),
                          player2.Position());
                printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                            player1.Name(), player1.My_item());
                printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                            player2.Name(), player2.My_item());
                //땅 주인이 없을 때 구매
                if (who_rand[player1.Position()] == 0) {
                    int cal1 = Gamestart[player1.Position()].rand;
                    int cal2 = Gamestart[player1.Position()].buila +
                               Gamestart[player1.Position()].rand;
                    int cal3 = Gamestart[player1.Position()].buila +
                               Gamestart[player1.Position()].rand +
                               Gamestart[player1.Position()].building;
                    int cal4 = Gamestart[player1.Position()].buila +
                               Gamestart[player1.Position()].rand +
                               Gamestart[player1.Position()].building +
                               Gamestart[player1.Position()].randmark;
                    printchoose((int)startx, (int)starty, (int)endx, (int)endy,
                                player1.Position());
                    if (player1.Turn() == 0) {
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 's' || num2 == 'd') {
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position());
                                printstatus(startx, endx / 2 - 1, endy,
                                            player1.Money(), player1.Name(),
                                            player1.My_item());
                                printstatus(endx / 2 + 1, endx, endy,
                                            player2.Money(), player2.Name(),
                                            player2.My_item());
                                break;
                            }
                        }
                        printbuy(startx, starty, endx, endy, player1.Turn(),
                                 building[player1.Position()], cal1, cal2, cal3,
                                 cal4);
                        if (num2 == 's') {
                            int cal1 = Gamestart[player1.Position()].rand;
                            int cal2 = Gamestart[player1.Position()].buila +
                                       Gamestart[player1.Position()].rand;
                            char num3;
                            while (1) {
                                num3 = getch();
                                if (num3 == '1') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 1;
                                    fee[player1.Position()] = cal1;
                                    player1.MoneyDcrease(cal1);
                                    break;
                                } else if (num3 == '2') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 2;
                                    fee[player1.Position()] = cal2;
                                    player1.MoneyDcrease(cal2);
                                    break;
                                }
                            }
                        }
                    } else if (player1.Turn() == 1) {
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 's' || num2 == 'd') {
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position());
                                printstatus(startx, endx / 2 - 1, endy,
                                            player1.Money(), player1.Name(),
                                            player1.My_item());
                                printstatus(endx / 2 + 1, endx, endy,
                                            player2.Money(), player2.Name(),
                                            player2.My_item());
                                break;
                            }
                        }
                        printbuy(startx, starty, endx, endy, player1.Turn(),
                                 building[player1.Position()], cal1, cal2, cal3,
                                 cal4);
                        if (num2 == 's') {
                            char num3;
                            while (1) {
                                num3 = getch();
                                mvprintw(22, 50, "%c", num3);
                                if (num3 == '1') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 1;
                                    fee[player1.Position()] = cal1;
                                    player1.MoneyDcrease(cal1);
                                    break;
                                } else if (num3 == '2') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 2;
                                    fee[player1.Position()] = cal2;
                                    player1.MoneyDcrease(cal2);
                                    break;
                                } else if (num3 == '3') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 3;
                                    fee[player1.Position()] = cal3;
                                    player1.MoneyDcrease(cal3);
                                    break;
                                }
                            }
                        }
                    } else if (player1.Turn() == 2) {
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 's' || num2 == 'd') {
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position());
                                printstatus(startx, endx / 2 - 1, endy,
                                            player1.Money(), player1.Name(),
                                            player1.My_item());
                                printstatus(endx / 2 + 1, endx, endy,
                                            player2.Money(), player2.Name(),
                                            player2.My_item());
                                break;
                            }
                        }
                        printbuy(startx, starty, endx, endy, player1.Turn(),
                                 building[player1.Position()], cal1, cal2, cal3,
                                 cal4);
                        if (num2 == 's') {
                            char num3;
                            while (1) {
                                num3 = getch();
                                mvprintw(22, 50, "%c", num3);
                                if (num3 == '1') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 1;
                                    fee[player1.Position()] = cal1;
                                    player1.MoneyDcrease(cal1);
                                    break;
                                } else if (num3 == '2') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 2;
                                    fee[player1.Position()] = cal2;
                                    player1.MoneyDcrease(cal2);
                                    break;
                                } else if (num3 == '3') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 3;
                                    fee[player1.Position()] = cal3;
                                    player1.MoneyDcrease(cal3);
                                    break;
                                } else if (num3 == '4') {
                                    who_rand[player1.Position()] = 1;
                                    building[player1.Position()] = 4;
                                    fee[player1.Position()] = cal4;
                                    player1.MoneyDcrease(cal4);
                                    break;
                                }
                            }
                        }
                    }
                }
                turn++;
            }
        } else if (turn == 1) {
            curs_set(0);
            noecho();
            printgame(startx, starty, endx, endy, player1.Position(),
                      player2.Position());

            printready(startx, starty, endx, endy, player2.Name());
            printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                        player1.Name(), player1.My_item());
            printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                        player2.Name(), player2.My_item());
            char num = getch();
            if (num == 'a') {
                player2.RandomDice();
                printrolldice(startx, starty, endx, endy, player2.Dice1(),
                              player2.Dice2());
                printresult(startx, starty, endx, endy, player2.Dice1(),
                            player2.Dice2());
                sleep(1);
                player2.move();
                printgame(startx, starty, endx, endy, player1.Position(),
                          player2.Position());
                if (who_rand[player2.Position()] ==
                    1) { // Player 1땅을 밟았을떄
                    player2.MoneyDcrease(fee[player2.Position()] * 2.2);
                    player1.MoneyIcrease(fee[player2.Position()] * 2.2);
                    // player1.MoneyIn
                }
                printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                            player1.Name(), player1.My_item());
                printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                            player2.Name(), player2.My_item());
                turn--;
            }
        }
    }
    endwin();
    return 0;
}
