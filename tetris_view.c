#include "common.h"
#include "tetris_model.h"
#include <stdio.h>

// 테트리스 전체 판과 우측 정보창을 그리는 함수
void drawTetrisBoard() {

    int startX = 4;
    int startY = 2;
    int infoX = 0;
    int boardTile = 0;
    int blockColors[] = { 11, 13, 14, 9, 12, 10, 4 };

    infoX = startX + (BOARD_WIDTH * 2) + 8;

    // 1. 게임판 출력
    for (int y = 0; y <= BOARD_HEIGHT; y++) {

        for (int x = 0; x <= BOARD_WIDTH + 1; x++) {

            gotoxy(startX + x * 2, startY + y);

            if (y == BOARD_HEIGHT) {

                setColor(7);

                if (x == 0) printf("+");
                else if (x == BOARD_WIDTH + 1) printf("+");
                else printf("--");
            }
            else if (x == 0 || x == BOARD_WIDTH + 1) {

                setColor(7);
                printf("||");
            }
            else {

                boardTile = g_board[y][x - 1];

                if (boardTile > 0) {
                    setColor(blockColors[boardTile - 1]);
                    printf("[]");
                }
                else {
                    setColor(8);
                    printf(". ");
                }
            }
        }
    }

    // 2. 정보창
    setColor(15);

    gotoxy(infoX, startY);
    printf("[ NEXT ]");

    gotoxy(infoX - 2, startY + 1);
    printf("+----------+");

    for (int i = 1; i <= 4; i++) {
        gotoxy(infoX - 2, startY + 1 + i);
        printf("|          |");
    }

    gotoxy(infoX - 2, startY + 6);
    printf("+----------+");

    // 3. 조작법
    setColor(7);

    gotoxy(infoX, startY + 9);
    printf("  0    메인메뉴");

    gotoxy(infoX, startY + 11);
    printf("<- ->  이동");

    gotoxy(infoX, startY + 13);
    printf("  V    하강");

    gotoxy(infoX, startY + 15);
    printf("Space  회전");
}

// NEXT 블럭 출력
void drawNextBlock() {

    int startX = 4;
    int startY = 2;
    int boxInnerX = startX + (BOARD_WIDTH * 2) + 8;
    int boxInnerY = startY + 2;
    int isBlock = 0;
    int blockColors[] = { 11, 13, 14, 9, 12, 10, 4 };

    for (int y = 0; y < 4; y++) {
        gotoxy(boxInnerX, boxInnerY + y);
        printf("        ");
    }

    setColor(blockColors[g_nextBlockType]);

    for (int y = 0; y < 4; y++) {

        gotoxy(boxInnerX, boxInnerY + y);

        for (int x = 0; x < 4; x++) {

            isBlock = g_blocks[g_nextBlockType][y][x];

            if (isBlock == 1)
                printf("[]");
            else
                printf("  ");
        }
    }
}

// 현재 블럭 출력
void drawCurrentBlock() {

    int startX = 4;
    int startY = 2;
    int isBlock;
    int rotX, rotY;
    int targetX, targetY;
    int blockColors[] = { 11, 13, 14, 9, 12, 10, 4 };

    setColor(blockColors[g_currentBlockType]);

    for (int y = 0; y < 4; y++) {

        for (int x = 0; x < 4; x++) {

            rotX = x;
            rotY = y;

            if (g_currentRotation == 1) { rotX = y; rotY = 3 - x; }
            else if (g_currentRotation == 2) { rotX = 3 - x; rotY = 3 - y; }
            else if (g_currentRotation == 3) { rotX = 3 - y; rotY = x; }

            isBlock = g_blocks[g_currentBlockType][rotY][rotX];

            if (isBlock == 1) {

                targetX = startX + (g_blockX + x + 1) * 2;
                targetY = startY + (g_blockY + y);

                if (g_blockX + x >= 0 &&
                    g_blockX + x < BOARD_WIDTH &&
                    g_blockY + y < BOARD_HEIGHT) {

                    gotoxy(targetX, targetY);
                    printf("[]");
                }
            }
        }
    }
}