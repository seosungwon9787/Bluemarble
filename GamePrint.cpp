#include "GamePrint.h"

void printtext(int startx, int starty, int endx, int endy, int p1_p, int p2_p) {
    string map_name[32] = {
        "출발점",   "강릉",          "아이템", "춘천",        "북한산", "경주",
        "안동",     "천안",          "감옥",   "서울 대공원", "인천",   "대전",
        "아이템",   "청주",          "설악산", "세종",        "엑스포", "여수",
        "지리산",   "제주",          "아이템", "포항",        "울산",   "대구",
        "기차여행", "어린이 대공원", "전주",   "광주",        "아이템", "부산",
        "세금",     "서울"};
    int j = endx - 9;
    for (int i = 0; i < 9; i++) {
        if (i == 0 || i == 2 || i == 8) {
            attron(COLOR_PAIR(BRIGHT_WHITE));
        } else if (i == 4) {
            attron(COLOR_PAIR(YELLOW));
        } else if (i < 4) {
            attron(COLOR_PAIR(BRIGHT_GREEN));
        } else {
            attron(COLOR_PAIR(GREEN));
        }
        mvprintw(endy - 2, j, "%s", map_name[i].c_str());
        if (p1_p == i) {
            attron(COLOR_PAIR(BLUE));
            mvprintw(endy - 1, j, "●");
        }
        if (p2_p == i) {
            attron(COLOR_PAIR(RED));
            mvprintw(endy - 1, j + 2, "●");
        }
        j -= 10;
    }
    j = endy - 5;
    for (int i = 9; i < 17; i++) {
        if (i == 12 || i == 16) {
            attron(COLOR_PAIR(BRIGHT_WHITE));
        } else if (i == 9 || i == 14) {
            attron(COLOR_PAIR(YELLOW));
        } else if (i < 12) {
            attron(COLOR_PAIR(BRIGHT_BLUE));
        } else {
            attron(COLOR_PAIR(BLUE));
        }
        if (i == 9) {
            mvprintw(j, startx + 1, "서울");
            mvprintw(j + 1, startx + 1, "대공원");
        } else {
            mvprintw(j, startx + 1, "%s", map_name[i].c_str());
        }
        if (p1_p == i) {
            attron(COLOR_PAIR(BLUE));
            mvprintw(j + 1, startx + 1, "●");
        }
        if (p2_p == i) {
            attron(COLOR_PAIR(RED));
            mvprintw(j + 1, startx + 3, "●");
        }
        j -= 3;
    }
    j = startx + 11;
    for (int i = 17; i < 25; i++) {
        if (i == 20 || i == 24) {
            attron(COLOR_PAIR(BRIGHT_WHITE));
        } else if (i == 18) {
            attron(COLOR_PAIR(YELLOW));
        } else if (i < 20) {
            attron(COLOR_PAIR(BRIGHT_Magenta));
        } else {
            attron(COLOR_PAIR(Magenta));
        }
        mvprintw(starty + 1, j, "%s", map_name[i].c_str());
        if (p1_p == i) {
            attron(COLOR_PAIR(BLUE));
            mvprintw(starty + 2, j, "●");
        }
        if (p2_p == i) {
            attron(COLOR_PAIR(RED));
            mvprintw(starty + 2, j + 2, "●");
        }
        j += 10;
    }
    j = starty + 4;
    for (int i = 25; i < 32; i++) {
        if (i == 28 || i == 30) {
            attron(COLOR_PAIR(BRIGHT_WHITE));
        } else if (i == 25) {
            attron(COLOR_PAIR(YELLOW));
        } else if (i < 28) {
            attron(COLOR_PAIR(BRIGHT_RED));
        } else {
            attron(COLOR_PAIR(RED));
        }
        if (i == 25) {
            mvprintw(j, endx - 9, "어린이");
            mvprintw(j + 1, endx - 9, "대공원");
        } else {
            mvprintw(j, endx - 9, "%s", map_name[i].c_str());
        }
        if (p1_p == i) {
            attron(COLOR_PAIR(BLUE));
            mvprintw(j + 1, endx - 9, "●");
        }
        if (p2_p == i) {
            attron(COLOR_PAIR(RED));
            mvprintw(j + 1, endx - 7, "●");
        }
        j += 3;
    }
}
void printline(int startx, int starty, int endx, int endy) {
    mvprintw(starty, startx,
             "-------------------------------------------------------"
             "------------------------------------");
    mvprintw(starty + 3, startx,
             "-------------------------------------------------------"
             "------------------------------------");
    mvprintw(endy - 3, startx,
             "-------------------------------------------------------"
             "------------------------------------");
    mvprintw(endy, startx,
             "-------------------------------------------------------"
             "------------------------------------");
    int j = starty + 6;
    for (int k = 0; k < 6; k++) {
        for (int i = startx + 1; i < endx + 1; i++) {
            if (i <= startx + 10 || i >= endx - 10) {
                mvprintw(j, i, "-");
            }
        }
        j += 3;
    }
    for (int i = starty + 1; i < endy; i++) {
        if (i != starty + 3 && i != endy - 3) {
            mvprintw(i, startx, "|");
        }
    }
    for (int i = starty + 1; i < endy; i++) {
        if (i != starty + 3 && i != endy - 3) {
            mvprintw(i, startx + 10, "|");
        }
    }
    for (int i = starty + 1; i < endy; i++) {
        if (i != starty + 3 && i != endy - 3) {
            mvprintw(i, endx, "|");
        }
    }
    for (int i = starty + 1; i < endy; i++) {
        if (i != starty + 3 && i != endy - 3) {
            mvprintw(i, endx - 10, "|");
        }
    }
    j = endx - 20;
    for (int k = 0; k < 6; k++) {
        for (int i = starty + 1; i < endy; i++) {
            if (i < starty + 3 || i > endy - 3) {
                mvprintw(i, j, "|");
            }
        }
        j -= 10;
    }
}
void printgame(int startx, int starty, int endx, int endy, int p1_p, int p2_p) {
    clear();
    string map_name[32] = {
        "출발점",   "강릉",          "아이템", "춘천",        "북한산", "경주",
        "안동",     "천안",          "감옥",   "서울 대공원", "인천",   "대전",
        "아이템",   "청주",          "설악산", "세종",        "엑스포", "여수",
        "지리산",   "제주",          "아이템", "포항",        "울산",   "대구",
        "기차여행", "어린이 대공원", "전주",   "광주",        "아이템", "부산",
        "세금",     "서울"};
    printline(startx, starty, endx, endy);
    printtext(startx, starty, endx, endy, p1_p, p2_p);
    refresh();
}
void printready(int startx, int starty, int endx, int endy, string name) {
    attron(COLOR_PAIR(BRIGHT_WHITE));
    int x = ((startx + endx) / 2) - 24;
    int y = (starty + endy) / 2 + 5;
    mvprintw(y, x, "%s님 차례입니다. a키를 눌러 주사위를 굴리세요!",
             name.c_str());
    refresh();
}

void printresult(int startx, int starty, int endx, int endy, int dice1,
                 int dice2) {
    attron(COLOR_PAIR(BRIGHT_WHITE));
    int x = ((startx + endx) / 2) - 18;
    int y = (starty + endy) / 2 + 5;
    mvprintw(y, x - 6,
             "                                                      ");
    mvprintw(y, x, "주사위가 %d, %d가 나와 %d칸 이동합니다!", dice1, dice2,
             dice1 + dice2);
    refresh();
}
void printstatus(int startx, int endx, int endy, int money, string name,
                 vector<string> Item) {
    attron(COLOR_PAIR(BRIGHT_WHITE));
    for (int i = startx; i <= endx; i++) {
        mvprintw(endy + 1, i, "-");
    }
    for (int i = startx; i <= endx; i++) {
        mvprintw(endy + 5, i, "-");
    }
    for (int i = endy + 2; i < endy + 5; i++) {
        mvprintw(i, startx, "|");
    }
    for (int i = endy + 2; i < endy + 5; i++) {
        mvprintw(i, endx, "|");
    }
    mvprintw(endy + 2, startx + 1, "%s", name.c_str());
    mvprintw(endy + 3, startx + 1, "재산 : %d", money);
    mvprintw(endy + 4, startx + 1, "아이템 : %s", Item);
    refresh();
}
void printrolldice(int startx, int starty, int endx, int endy, int dice1,
                   int dice2) {
    attron(COLOR_PAIR(BRIGHT_WHITE));
    int dice_x1 = ((startx + endx) / 2) - 14;
    int dice_y1 = (starty + endy) / 2 - 5;
    int dice_x2 = ((startx + endx) / 2) + 2;
    int dice_y2 = (starty + endy) / 2 - 5;
    //첫번째 주사위 출력
    for (int i = dice_x1; i < dice_x1 + 12; i++) {
        mvprintw(dice_y1, i, "━");
    }
    mvprintw(dice_y1, dice_x1 - 1, "┏");
    mvprintw(dice_y1, dice_x1 + 12, "┓");
    for (int i = dice_x1; i < dice_x1 + 12; i++) {
        mvprintw(dice_y1 + 6, i, "━");
    }
    mvprintw(dice_y1 + 6, dice_x1 - 1, "┗");
    mvprintw(dice_y1 + 6, dice_x1 + 12, "┛ ");
    for (int i = dice_y1 + 1; i < dice_y1 + 6; i++) {
        mvprintw(i, dice_x1 - 1, "┃");
    }
    for (int i = dice_y1 + 1; i < dice_y1 + 6; i++) {
        mvprintw(i, dice_x1 + 12, "┃");
    }
    if (dice1 == 1) {
        mvprintw(dice_y1 + 3, dice_x1 + 5, "●");
    }
    if (dice1 == 2) {
        mvprintw(dice_y1 + 3, dice_x1 + 3, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 7, "●");
    }
    if (dice1 == 3) {
        mvprintw(dice_y1 + 3, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 5, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 8, "●");
    }
    if (dice1 == 4) {
        mvprintw(dice_y1 + 1, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 1, dice_x1 + 8, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 8, "●");
    }
    if (dice1 == 5) {
        mvprintw(dice_y1 + 1, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 1, dice_x1 + 8, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 8, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 5, "●");
    }
    if (dice1 == 6) {
        mvprintw(dice_y1 + 1, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 1, dice_x1 + 8, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 5, dice_x1 + 8, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 2, "●");
        mvprintw(dice_y1 + 3, dice_x1 + 8, "●");
    }
    //두번째 주사위 출력
    for (int i = dice_x2; i < dice_x2 + 12; i++) {
        mvprintw(dice_y2, i, "━");
    }
    mvprintw(dice_y2, dice_x2 - 1, "┏");
    mvprintw(dice_y2, dice_x2 + 12, "┓");
    for (int i = dice_x2; i < dice_x2 + 12; i++) {
        mvprintw(dice_y2 + 6, i, "━");
    }
    mvprintw(dice_y2 + 6, dice_x2 - 1, "┗");
    mvprintw(dice_y2 + 6, dice_x2 + 12, "┛ ");
    for (int i = dice_y2 + 1; i < dice_y2 + 6; i++) {
        mvprintw(i, dice_x2 - 1, "┃");
    }
    for (int i = dice_y2 + 1; i < dice_y2 + 6; i++) {
        mvprintw(i, dice_x2 + 12, "┃");
    }
    if (dice2 == 1) {
        mvprintw(dice_y2 + 3, dice_x2 + 5, "●");
    }
    if (dice2 == 2) {
        mvprintw(dice_y2 + 3, dice_x2 + 3, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 7, "●");
    }
    if (dice2 == 3) {
        mvprintw(dice_y2 + 3, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 5, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 8, "●");
    }
    if (dice2 == 4) {
        mvprintw(dice_y2 + 1, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 1, dice_x2 + 8, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 8, "●");
    }
    if (dice2 == 5) {
        mvprintw(dice_y2 + 1, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 1, dice_x2 + 8, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 8, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 5, "●");
    }
    if (dice2 == 6) {
        mvprintw(dice_y2 + 1, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 1, dice_x2 + 8, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 5, dice_x2 + 8, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 2, "●");
        mvprintw(dice_y2 + 3, dice_x2 + 8, "●");
    }
    refresh();
}

void printbuy(int startx, int starty, int endx, int endy, int turn,
              int building, int cal1, int cal2, int cal3, int cal4) {
    attron(COLOR_PAIR(BRIGHT_WHITE));
    int x = ((startx + endx) / 2) - 25;
    int y = ((starty + endy) / 2);
    for (int i = x; i < x + 50; i++) {
        mvprintw(y + 6, i, "-");
    }
    for (int i = x; i < x + 50; i++) {
        mvprintw(y - 4, i, "-");
    }
    for (int i = y - 3; i < y + 6; i++) {
        mvprintw(i, x, "|");
    }
    for (int i = y - 3; i < y + 6; i++) {
        mvprintw(i, x + 49, "|");
    }
    if (turn == 0) {
        mvprintw(y, x + 2, "1 : 땅");
        mvprintw(y + 2, x + 2, "2 : 땅+빌라");
        mvprintw(y, x + 35, "%d원", cal1);
        mvprintw(y + 2, x + 35, "%d원", cal2);
    } else if (turn == 1) {
        mvprintw(y - 2, x + 2, "1 : 땅");
        mvprintw(y + 1, x + 2, "2 : 땅+빌라");
        mvprintw(y + 4, x + 2, "3 : 땅+빌라+빌딩");
        mvprintw(y - 2, x + 35, "%d원", cal1);
        mvprintw(y + 1, x + 35, "%d원", cal2);
        mvprintw(y + 4, x + 35, "%d원", cal3);
    } else {
        mvprintw(y - 2, x + 2, "1 : 땅");
        mvprintw(y, x + 2, "2 : 땅+빌라");
        mvprintw(y + 2, x + 2, "3 : 땅+빌라+빌딩");
        mvprintw(y + 4, x + 2, "4 : 땅+빌라+빌딩+호텔");
        mvprintw(y - 2, x + 35, "%d원", cal1);
        mvprintw(y, x + 35, "%d원", cal2);
        mvprintw(y + 2, x + 35, "%d원", cal3);
        mvprintw(y + 4, x + 35, "%d원", cal4);
    }
    refresh();
}
void printchoose(int startx, int starty, int endx, int endy, int name) {
    string map_name[32] = {
        "출발점",   "강릉",          "아이템", "춘천",        "북한산", "경주",
        "안동",     "천안",          "감옥",   "서울 대공원", "인천",   "대전",
        "아이템",   "청주",          "설악산", "세종",        "엑스포", "여수",
        "지리산",   "제주",          "아이템", "포항",        "울산",   "대구",
        "기차여행", "어린이 대공원", "전주",   "광주",        "아이템", "부산",
        "세금",     "서울"};
    attron(COLOR_PAIR(BRIGHT_WHITE));
    int x = ((startx + endx) / 2) - 25;
    int y = ((starty + endy) / 2);
    for (int i = x; i < x + 50; i++) {
        mvprintw(y + 3, i, "-");
    }
    for (int i = x; i < x + 50; i++) {
        mvprintw(y - 2, i, "-");
    }
    for (int i = y - 1; i < y + 3; i++) {
        mvprintw(i, x, "|");
    }
    for (int i = y - 1; i < y + 3; i++) {
        mvprintw(i, x + 49, "|");
    }
    mvprintw(y - 1, x + 1, "%s을 구매하시겠습니까?", map_name[name].c_str());
    mvprintw(y + 1, x + 10, "s : 구매");
    mvprintw(y + 1, x + 32, "d : 취소");
    refresh();
}
