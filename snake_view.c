#include "snake_model.h"
#include "common.h"

int getKeyDown() {

    if (_kbhit())
        return _getch();

    return -1;
}

void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]) {

    int i, j;

    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            gotoxy(i * 2, j);

            if (map[i][j] == WALL)
                printf("#");
            else
                printf(" ");
        }
    }
}

void drawSubMap(int score, int best) {

    gotoxy(0, MAP_SIZE + 1);
    printf("Best Score : %d", best);

    gotoxy(0, MAP_SIZE + 2);
    printf("Your Score : %d", score);
}

int drawStartMenu() {

    while (1) {

        system("cls");

        gotoxy(10, 5);
        printf("===== Snake Game =====");

        gotoxy(10, 7);
        printf("Press S To Start");

        gotoxy(10, 8);
        printf("Press O To Exit");

        int keyDown = getKeyDown();

        if (keyDown == 's' || keyDown == 'S')
            return TRUE;

        if (keyDown == 'o' || keyDown == 'O')
            return FALSE;

        Sleep(100);
    }
}
