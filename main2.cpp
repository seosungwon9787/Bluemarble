#include "GamePrint.h"
#include <fcntl.h>
#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include <ncursesw/curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
#define MSG_SIZE (sizeof(sendP) - sizeof(long))
#define MSG_SIZE2 (sizeof(GameStart) - sizeof(long))
using namespace std;
void signalHandler(int signum);
int msqid1 = 0;
int msqid2 = 0;
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
    signal(SIGINT, signalHandler);
    int startx = 0;
    int starty = 0;
    int endx = 90;
    int endy = 27;
    bool iswin = false;
    string map_name[32] = {
        "출발점",   "강릉",         "아이템", "춘천",       "북한산",   "경주",
        "안동",     "천안",         "감옥",   "서울대공원", "인천",     "대전",
        "아이템",   "청주",         "설악산", "세종",       "국내비행", "여수",
        "지리산",   "제주",         "아이템", "포항",       "울산",     "대구",
        "기차여행", "어린이대공원", "전주",   "광주",       "아이템",   "부산",
        "세금",     "서울"};
    int who_rand[32] = {-1, 0, -3, 0, 0,  0, 0, 0, -4, 0, 0, 0, -3, 0, 0,  0,
                        -5, 0, 0,  0, -3, 0, 0, 0, -5, 0, 0, 0, -3, 0, -2, 0};
    int building[32] = {
        0,
    };
    int fee[32] = {
        0,
    };
    int iftravel = 0;
    string item = "반값할인";
    Land Gamestart[32];
    SettingGame(Gamestart);
    GamePlayer player1("player1", 2000000);
    GamePlayer player2("player2", 2000000);
    msqid1 = msgget(1, IPC_CREAT);
    msqid2 = msgget(2, IPC_CREAT | 0600);
    int turn = 1;
    int turn2 = 2;
    int iscape = 0;
    Start start;
    memset(&start, 0x00, sizeof(Start));
    start.pid = 1;
    start.start = true;
    int suc = msgsnd(msqid1, &start, MSG_SIZE2, 0);
    if (suc == -1) {
        perror("msgsnd() error!");
        exit(1);
    }
    printsuccess(startx, starty, endx, endy);
    sleep(2);
    while (1) {
        if (turn == 0) {
            curs_set(0);
            noecho();
            if (iscape > 0) {
                printgame(startx, starty, endx, endy, player1.Position(),
                          player2.Position(), who_rand, building);
                printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                            player1.Name(), player1.Item());
                printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                            player2.Name(), player2.Item());
                printremainprison(startx, starty, endx, endy, iscape);
                sleep(2);
                iscape--;
                turn++;
                continue;
            }
            printgame(startx, starty, endx, endy, player1.Position(),
                      player2.Position(), who_rand, building);
            printready(startx, starty, endx, endy, player2.Name());
            printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                        player1.Name(), player1.Item());
            printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                        player2.Name(), player2.Item());
            char num = getch();
            if (num == 'a') {
                if (iftravel == 0) {
                    player2.RandomDice();
                    printrolldice(startx, starty, endx, endy, player2.Dice1(),
                                  player2.Dice2());
                    printresult(startx, starty, endx, endy, player2.Dice1(),
                                player2.Dice2());
                    sleep(1);
                    player2.move();
                }
                iftravel = 0;
                printgame(startx, starty, endx, endy, player1.Position(),
                          player2.Position(), who_rand, building);
                printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                            player1.Name(), player1.Item());
                printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                            player2.Name(), player2.Item());
                //땅 주인이 없을 때 구매
                if (who_rand[player2.Position()] == 0) {
                    int cal1 = Gamestart[player2.Position()].rand;
                    int cal2 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand;
                    int cal3 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand +
                               Gamestart[player2.Position()].building;
                    int cal4 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand +
                               Gamestart[player2.Position()].building +
                               Gamestart[player2.Position()].randmark;
                    printchoose((int)startx, (int)starty, (int)endx, (int)endy,
                                player2.Position());
                    char num2;
                    while (1) {
                        num2 = getch();
                        if (num2 == 's' || num2 == 'd') {
                            printgame(startx, starty, endx, endy,
                                      player1.Position(), player2.Position(),
                                      who_rand, building);
                            printstatus(startx, endx / 2 - 1, endy,
                                        player1.Money(), player1.Name(),
                                        player1.Item());
                            printstatus(endx / 2 + 1, endx, endy,
                                        player2.Money(), player2.Name(),
                                        player2.Item());
                            break;
                        }
                    }
                    if (num2 == 's' && player2.Money() < cal1) {
                        printlackmoney(startx, starty, endx, endy);
                        sleep(1);
                        turn++;
                        continue;
                    }
                    if (Gamestart[player2.Position()].buila == 0) {
                        printTour(startx, starty, endx, endy, player2.Turn(),
                                  building[player2.Position()], cal1);
                    } else {
                        printbuy(startx, starty, endx, endy, player2.Turn(),
                                 building[player2.Position()], cal1, cal2, cal3,
                                 cal4);
                    }
                    if (Gamestart[player2.Position()].buila == 0) {
                        if (num2 == 's') {
                            char num3;
                            while (1) {
                                num3 = getch();
                                if (num3 == '1') {
                                    who_rand[player2.Position()] = 2;
                                    building[player2.Position()] = 1;
                                    fee[player2.Position()] =
                                        Gamestart[player2.Position()].pass1;
                                    ;
                                    player2.MoneyDcrease(cal1);
                                    break;
                                }
                            }
                        }
                    } else {
                        if (num2 == 's') {
                            char num3;
                            while (1) {
                                num3 = getch();
                                if (num3 == '1') {
                                    who_rand[player2.Position()] = 2;
                                    building[player2.Position()] = 1;
                                    fee[player2.Position()] =
                                        Gamestart[player2.Position()].pass1;
                                    player2.MoneyDcrease(cal1);
                                    break;
                                } else if (num3 == '2') {
                                    if (player2.Money() < cal2) {
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printlackmoney(startx, starty, endx,
                                                       endy);
                                        sleep(1);
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printbuy(startx, starty, endx, endy,
                                                 player2.Turn(),
                                                 building[player2.Position()],
                                                 cal1, cal2, cal3, cal4);
                                        continue;
                                    } else {
                                        who_rand[player2.Position()] = 2;
                                        building[player2.Position()] = 2;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass2;
                                        player2.MoneyDcrease(cal2);
                                        break;
                                    }
                                } else if (num3 == '3') {
                                    if (player2.Money() < cal3) {
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printlackmoney(startx, starty, endx,
                                                       endy);
                                        sleep(1);
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printbuy(startx, starty, endx, endy,
                                                 player2.Turn(),
                                                 building[player2.Position()],
                                                 cal1, cal2, cal3, cal4);
                                        continue;
                                    } else {
                                        who_rand[player2.Position()] = 2;
                                        building[player2.Position()] = 3;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass3;
                                        player2.MoneyDcrease(cal3);
                                        break;
                                    }
                                } else if (num3 == '4') {
                                    if (player2.Money() < cal4) {
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printlackmoney(startx, starty, endx,
                                                       endy);
                                        sleep(1);
                                        printgame(startx, starty, endx, endy,
                                                  player1.Position(),
                                                  player2.Position(), who_rand,
                                                  building);
                                        printstatus(startx, endx / 2 - 1, endy,
                                                    player1.Money(),
                                                    player1.Name(),
                                                    player1.Item());
                                        printstatus(endx / 2 + 1, endx, endy,
                                                    player2.Money(),
                                                    player2.Name(),
                                                    player2.Item());
                                        printbuy(startx, starty, endx, endy,
                                                 player1.Turn(),
                                                 building[player1.Position()],
                                                 cal1, cal2, cal3, cal4);
                                        continue;
                                    } else {
                                        who_rand[player2.Position()] = 2;
                                        building[player2.Position()] = 4;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass4;
                                        player2.MoneyDcrease(cal4);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                } else if (who_rand[player2.Position()] == 2) {
                    int cal1 = Gamestart[player2.Position()].buila;
                    int cal2 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].building;
                    int cal3 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].building +
                               Gamestart[player2.Position()].hotel;
                    int cal4 = Gamestart[player2.Position()].building;
                    int cal5 = Gamestart[player2.Position()].building +
                               Gamestart[player2.Position()].hotel;
                    int cal6 = Gamestart[player2.Position()].hotel;
                    int cal7 = Gamestart[player2.Position()].randmark;
                    if (building[player2.Position()] == 4) {
                        if (player2.Money() < cal7) {
                            printlackmoney(startx, starty, endx, endy);
                            sleep(1);
                            turn++;
                            continue;
                        }
                        printrandmark(startx, starty, endx, endy,
                                      player2.Position(),
                                      building[player2.Position()], cal7);
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 's') {
                                player2.MoneyDcrease(cal7);
                                who_rand[player2.Position()] = 2;
                                building[player2.Position()] = 5;
                                fee[player2.Position()] = cal7;
                                break;
                            } else {
                                break;
                            }
                        }
                    } else if (Gamestart[player2.Position()].buila != 0) {
                        printaddchoose((int)startx, (int)starty, (int)endx,
                                       (int)endy, player2.Position());
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 's' || num2 == 'd') {
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position(), who_rand,
                                          building);
                                printstatus(startx, endx / 2 - 1, endy,
                                            player1.Money(), player1.Name(),
                                            player1.Item());
                                printstatus(endx / 2 + 1, endx, endy,
                                            player2.Money(), player2.Name(),
                                            player2.Item());
                                break;
                            }
                        }
                        if (building[player2.Position()] == 1) {
                            if (num2 == 's' && player2.Money() < cal1) {
                                printlackmoney(startx, starty, endx, endy);
                                sleep(1);
                                turn++;
                                continue;
                            }
                        } else if (building[player2.Position()] == 2) {
                            if (num2 == 's' && player2.Money() < cal4) {
                                printlackmoney(startx, starty, endx, endy);
                                sleep(1);
                                turn++;
                                continue;
                            }
                        } else if (building[player2.Position()] == 3) {
                            if (num2 == 's' && player2.Money() < cal6) {
                                printlackmoney(startx, starty, endx, endy);
                                sleep(1);
                                turn++;
                                continue;
                            }
                        }
                        printadd(startx, starty, endx, endy, player2.Turn(),
                                 building[player2.Position()], cal1, cal2, cal3,
                                 cal4, cal5, cal6);
                        if (num2 == 's') {
                            char num3;
                            if (building[player2.Position()] == 1) {
                                while (1) {
                                    num3 = getch();
                                    if (num3 == '1') {
                                        building[player2.Position()] = 2;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass2;
                                        player2.MoneyDcrease(cal1);
                                        break;
                                    } else if (num3 == '2') {
                                        if (player2.Money() < cal2) {
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printlackmoney(startx, starty, endx,
                                                           endy);
                                            sleep(1);
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printadd(
                                                startx, starty, endx, endy,
                                                player2.Turn(),
                                                building[player2.Position()],
                                                cal1, cal2, cal3, cal4, cal5,
                                                cal6);
                                            continue;
                                        } else {
                                            building[player2.Position()] = 3;
                                            fee[player2.Position()] =
                                                Gamestart[player2.Position()]
                                                    .pass3;
                                            player2.MoneyDcrease(cal2);
                                            break;
                                        }
                                    } else if (num3 == '3') {
                                        if (player2.Money() < cal3) {
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printlackmoney(startx, starty, endx,
                                                           endy);
                                            sleep(1);
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printadd(
                                                startx, starty, endx, endy,
                                                player2.Turn(),
                                                building[player2.Position()],
                                                cal1, cal2, cal3, cal4, cal5,
                                                cal6);
                                            continue;
                                        } else {
                                            building[player2.Position()] = 4;
                                            fee[player2.Position()] =
                                                Gamestart[player2.Position()]
                                                    .pass4;
                                            player2.MoneyDcrease(cal3);
                                            break;
                                        }
                                    }
                                }
                            } else if (building[player2.Position()] == 2) {
                                while (1) {
                                    num3 = getch();
                                    if (num3 == '1') {
                                        building[player2.Position()] = 3;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass3;
                                        player2.MoneyDcrease(cal4);
                                        break;
                                    } else if (num3 == '2') {
                                        if (player2.Money() < cal5) {
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printlackmoney(startx, starty, endx,
                                                           endy);
                                            sleep(1);
                                            printgame(startx, starty, endx,
                                                      endy, player1.Position(),
                                                      player2.Position(),
                                                      who_rand, building);
                                            printstatus(startx, endx / 2 - 1,
                                                        endy, player1.Money(),
                                                        player1.Name(),
                                                        player1.Item());
                                            printstatus(endx / 2 + 1, endx,
                                                        endy, player2.Money(),
                                                        player2.Name(),
                                                        player2.Item());
                                            printadd(
                                                startx, starty, endx, endy,
                                                player2.Turn(),
                                                building[player2.Position()],
                                                cal1, cal2, cal3, cal4, cal5,
                                                cal6);
                                            continue;
                                        } else {
                                            building[player2.Position()] = 4;
                                            fee[player2.Position()] =
                                                Gamestart[player2.Position()]
                                                    .pass4;
                                            player2.MoneyDcrease(cal5);
                                            break;
                                        }
                                    }
                                }
                            } else if (building[player2.Position()] == 3) {
                                while (1) {
                                    num3 = getch();
                                    if (num3 == '1') {
                                        building[player2.Position()] = 4;
                                        fee[player2.Position()] =
                                            Gamestart[player2.Position()].pass4;
                                        player2.MoneyDcrease(cal6);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                } else if (who_rand[player2.Position()] == 1) {
                    if (player2.Item() == 0) {
                        printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                                    player1.Name(), player1.Item());
                        printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                                    player2.Name(), player2.Item());
                        player2.MoneyDcrease(fee[player2.Position()]);
                        player1.MoneyIcrease(fee[player2.Position()]);
                        int i = 1;
                        printgame(startx, starty, endx, endy,
                                  player1.Position(), player2.Position(),
                                  who_rand, building);
                        printlosemoney(startx, starty, endx, endy, i,
                                       fee[player2.Position()]);
                        sleep(1);
                    }
                    if (player1.Item() == 1) {
                        char num4;
                        printitemuse(startx, starty, endx, endy);
                        while (1) {
                            num4 = getch();
                            if (num4 == 'y' || num4 == 'n') {
                                break;
                            }
                        }
                        if (num4 == 'y') { // use item? yes
                            player2.MoneyDcrease(fee[player2.Position()] / 2);
                            player1.MoneyIcrease(fee[player2.Position()] / 2);
                            player2.hasitem(-1);
                            int i = 1;
                            printgame(startx, starty, endx, endy,
                                      player1.Position(), player2.Position(),
                                      who_rand, building);
                            printlosemoney(startx, starty, endx, endy, i,
                                           fee[player2.Position()] / 2);
                            printstatus(startx, endx / 2 - 1, endy,
                                        player1.Money(), player1.Name(),
                                        player1.Item());
                            printstatus(endx / 2 + 1, endx, endy,
                                        player2.Money(), player2.Name(),
                                        player2.Item());
                            sleep(1);
                        } else if (num4 == 'n') { // use item? No
                            player2.MoneyDcrease(fee[player2.Position()]);
                            player1.MoneyIcrease(fee[player2.Position()]);
                            int i = 1;
                            printgame(startx, starty, endx, endy,
                                      player1.Position(), player2.Position(),
                                      who_rand, building);
                            printlosemoney(startx, starty, endx, endy, i,
                                           fee[player2.Position()]);
                            printstatus(startx, endx / 2 - 1, endy,
                                        player1.Money(), player1.Name(),
                                        player1.Item());
                            printstatus(endx / 2 + 1, endx, endy,
                                        player2.Money(), player2.Name(),
                                        player2.Item());
                            sleep(1);
                        }
                    }
                    //파산되면 while문 종료
                    if (player2.Money() < 0) {
                        iswin = true;
                        turn++;
                        continue;
                    }
                    printgame(startx, starty, endx, endy, player1.Position(),
                              player2.Position(), who_rand, building);
                    printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                                player1.Name(), player1.Item());
                    printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                                player2.Name(), player2.Item());
                    int cal1 = Gamestart[player2.Position()].rand;
                    int cal2 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand;
                    int cal3 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand +
                               Gamestart[player2.Position()].building;
                    int cal4 = Gamestart[player2.Position()].buila +
                               Gamestart[player2.Position()].rand +
                               Gamestart[player2.Position()].building +
                               Gamestart[player2.Position()].hotel;
                    int stm;
                    if (building[player2.Position()] == 1) {
                        stm = cal1;
                    } else if (building[player2.Position()] == 2) {
                        stm = cal2;
                    } else if (building[player2.Position()] == 3) {
                        stm = cal3;
                    } else if (building[player2.Position()] == 4) {
                        stm = cal4;
                    }
                    if (building[player2.Position()] != 5 &&
                        player2.Money() >= stm && player2.Position() != 4 &&
                        player2.Position() != 9 && player2.Position() != 14 &&
                        player2.Position() != 18 && player2.Position() != 25) {
                        printtakeover(startx, starty, endx, endy,
                                      player2.Position(), stm);
                        char num2;
                        while (1) {
                            num2 = getch();
                            if (num2 == 'd') {
                                break;
                            }
                            if (num2 == 's') {
                                player2.MoneyDcrease(stm * 2);
                                player1.MoneyIcrease(stm * 2);
                                who_rand[player2.Position()] = 2;
                                fee[player2.Position()] = stm;
                                break;
                            }
                        }
                    }
                } else if (who_rand[player2.Position()] == -2) {
                    printtax((int)startx, (int)starty, (int)endx, (int)endy);
                    player2.MoneyDcrease(50000);
                    sleep(2);
                } // case of player on items
                else if (who_rand[player2.Position()] == -3) {
                    printItemGet((int)startx, (int)starty, (int)endx, (int)endy,
                                 player2.Item());
                    if (player2.Item() == 0) {
                        player2.hasitem(1);
                    }
                    sleep(2);
                } else if (who_rand[player2.Position()] == -4) {
                    iscape = 3;
                    printexplainprison(startx, starty, endx, endy);
                    sleep(2);
                } // case of player2 on travel
                else if (who_rand[player2.Position()] == -6) {
                    char num_t;
                    while (1) {
                        printtravel(startx, starty, endx, endy);
                        num_t = 'p';
                        num_t = getch();
                        if (num_t == 'z') {
                            if (player2.Position() != 0) {
                                player2.PositionMove(-1);
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position(), who_rand,
                                          building);
                                printstatus(startx, endx, endy, player1.Money(),
                                            player1.Name(), player1.Item());
                                printstatus(startx, endx, endy, player2.Money(),
                                            player2.Name(), player2.Item());
                            } else {
                                player2.PositionMove(31);
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position(), who_rand,
                                          building);
                                printstatus(startx, endx, endy, player1.Money(),
                                            player1.Name(), player1.Item());
                                printstatus(startx, endx, endy, player2.Money(),
                                            player2.Name(), player2.Item());
                            }
                        } else if (num_t == 'x') {
                            if (player2.Position() != 31) {
                                player2.PositionMove(1);
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position(), who_rand,
                                          building);
                                printstatus(startx, endx, endy, player1.Money(),
                                            player1.Name(), player1.Item());
                                printstatus(startx, endx, endy, player2.Money(),
                                            player2.Name(), player2.Item());
                            } else {
                                player2.PositionMove(-31);
                                printgame(startx, starty, endx, endy,
                                          player1.Position(),
                                          player2.Position(), who_rand,
                                          building);
                                printstatus(startx, endx, endy, player1.Money(),
                                            player1.Name(), player1.Item());
                                printstatus(startx, endx, endy, player2.Money(),
                                            player2.Name(), player2.Item());
                            }
                        } else if (num_t == 'a') {
                            turn--;
                            iftravel = 1;
                            break;
                        } else
                            continue;
                    }
                }
                turn++;
            }
        } else if (turn == 1) {
            if (turn2 > 2) {
                sendP sendp;
                memset(&sendp, 0x00, sizeof(sendP));
                sendp.pid = getpid();
                for (int i = 0; i < 32; i++) {
                    sendp.building[i] = building[i];
                    sendp.who_rand[i] = who_rand[i];
                    sendp.fee[i] = fee[i];
                }
                sendp.isover = false;
                sendp.money1 = player1.Money();
                sendp.money2 = player2.Money();
                sendp.Onitem = player2.getitem();
                sendp.position = player2.Position();
                sendp.isover = 0;
                if (iswin == true) {
                    sendp.isover = 2;
                    int fd = 0;
                    char *pathname = "./who_win.txt";
                    fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
                    if (fd == -1) {
                        perror("open() error!");
                        exit(-1);
                    }
                    char *lose = "player1 : win\tplayer2 : lose\n";
                    ssize_t wsize = 0;
                    wsize = write(fd, (char *)lose, strlen(lose));
                    if (wsize == -1) {
                        perror("write() error!");
                        exit(-2);
                    }
                    clear();
                    printwinner(startx, starty, endx, endy, player1.Name());
                    sleep(2);
                }
                int suc = msgsnd(msqid1, &sendp, MSG_SIZE, 0);
                if (suc == -1) {
                    perror("msgsnd() error!");
                    exit(1);
                }
            }
            if (iswin == true) {
                break;
            }
            sendP sendp2;
            memset(&sendp2, 0x00, sizeof(sendP));
            printgame(startx, starty, endx, endy, player1.Position(),
                      player2.Position(), who_rand, building);
            printwait2(startx, starty, endx, endy);
            printstatus(startx, endx / 2 - 1, endy, player1.Money(),
                        player1.Name(), player1.Item());
            printstatus(endx / 2 + 1, endx, endy, player2.Money(),
                        player2.Name(), player2.Item());
            msgrcv(msqid2, &sendp2, MSG_SIZE, 0, 0);
            if (sendp2.isover == 1) {
                clear();
                printwinner(startx, starty, endx, endy, player2.Name());
                break;
            } else if (sendp2.isover == 2) {
                clear();
                printwinner(startx, starty, endx, endy, player1.Name());
                break;
            }
            for (int i = 0; i < 32; i++) {
                building[i] = sendp2.building[i];
                who_rand[i] = sendp2.who_rand[i];
                fee[i] = sendp2.fee[i];
            }
            player1.setMoney(sendp2.money1);
            player2.setMoney(sendp2.money2);
            player1.setposition(sendp2.position);
            player1.setitem(sendp2.Onitem);
            turn--;
            turn2++;
        }
    }
    endwin();
    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid1, IPC_RMID, NULL);
        msgctl(msqid2, IPC_RMID, NULL);
        endwin();
        exit(0);
    }
}
