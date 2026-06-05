#include "common.h"
#include "tetris_model.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void drawTetrisBoard();
void drawNextBlock();
void drawCurrentBlock();

// checkCollision() - 충돌 검사 로직
int checkCollision(int nx, int ny, int nRot) {

    int rotX = 0;
    int rotY = 0;
    int targetX = 0;
    int targetY = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            rotX = x;
            rotY = y;

            if (nRot == 1) { rotX = y; rotY = 3 - x; }
            else if (nRot == 2) { rotX = 3 - x; rotY = 3 - y; }
            else if (nRot == 3) { rotX = 3 - y; rotY = x; }

            if (g_blocks[g_currentBlockType][rotY][rotX] == 1) {

                targetX = nx + x;
                targetY = ny + y;

                if (targetX < 0 || targetX >= BOARD_WIDTH || targetY >= BOARD_HEIGHT)
                    return 1;

                if (targetY >= 0 && g_board[targetY][targetX] > 0)
                    return 1;
            }
        }
    }

    return 0;
}

// 새로운 블럭 생성 및 초기화
void createNewBlock() {

    g_blockX = 3;
    g_blockY = 0;
    g_currentRotation = 0;

    g_currentBlockType = g_nextBlockType;
    g_nextBlockType = rand() % 7;

    drawNextBlock();

    if (checkCollision(g_blockX, g_blockY, g_currentRotation)) {

        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                g_board[y][x] = 0;
            }
        }

        system("cls");
        gotoxy(14, 12);
        setColor(12);
        printf("G A M E   O V E R");
        Sleep(2000);
    }
}

// 바닥 안착 블럭 고정
void lockBlock() {

    int rotX = 0;
    int rotY = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            rotX = x;
            rotY = y;

            if (g_currentRotation == 1) { rotX = y; rotY = 3 - x; }
            else if (g_currentRotation == 2) { rotX = 3 - x; rotY = 3 - y; }
            else if (g_currentRotation == 3) { rotX = 3 - y; rotY = x; }

            if (g_blocks[g_currentBlockType][rotY][rotX] == 1) {

                if (g_blockY + y >= 0)
                    g_board[g_blockY + y][g_blockX + x] = g_currentBlockType + 1;
            }
        }
    }
}

// 줄 삭제
void clearLines() {

    int isLineFull;
    int ty, tx;

    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {

        isLineFull = 1;

        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (g_board[y][x] == 0) {
                isLineFull = 0;
                break;
            }
        }

        if (isLineFull) {

            for (ty = y; ty > 0; ty--) {
                for (tx = 0; tx < BOARD_WIDTH; tx++) {
                    g_board[ty][tx] = g_board[ty - 1][tx];
                }
            }

            for (tx = 0; tx < BOARD_WIDTH; tx++) {
                g_board[0][tx] = 0;
            }

            y++;
        }
    }
}

// 블럭 회전
void rotateBlock() {

    int nextRot = (g_currentRotation + 1) % 4;

    if (!checkCollision(g_blockX, g_blockY, nextRot))
        g_currentRotation = nextRot;
}

// 테트리스 메인
 playTetris() {

    DWORD lastTick = GetTickCount();
    DWORD currentTick;
    DWORD gravityDelay = 600;
    int key;

    srand((unsigned)time(NULL));

    g_currentBlockType = rand() % 7;
    g_nextBlockType = rand() % 7;

    system("cls");

    drawTetrisBoard();
    drawNextBlock();

    g_blockX = 3;
    g_blockY = 0;
    g_currentRotation = 0;

    while (1) {

        // 중력 처리
        currentTick = GetTickCount();

        if (currentTick - lastTick >= gravityDelay) {

            if (!checkCollision(g_blockX, g_blockY + 1, g_currentRotation))
                g_blockY++;
            else {
                lockBlock();
                clearLines();
                createNewBlock();
            }

            lastTick = currentTick;
        }

        // 입력 처리
        if (_kbhit()) {

            key = _getch();

            // o : 메인 화면 복귀
            if (key == 'o' || key == 'O') {
                return 0;
            }  

            // 회전
            if (key == ' ') {
                rotateBlock();
            }

            // 하강
            if (key == 'v' || key == 'V') {
                if (!checkCollision(g_blockX, g_blockY + 1, g_currentRotation))
                    g_blockY++;
            }

            // 방향키
            if (key == 224) {

                key = _getch();

                switch (key) {

                case 75: // 왼쪽
                    if (!checkCollision(g_blockX - 1, g_blockY, g_currentRotation))
                        g_blockX--;
                    break;

                case 77: // 오른쪽
                    if (!checkCollision(g_blockX + 1, g_blockY, g_currentRotation))
                        g_blockX++;
                    break;
                }
            }
        }

        // 렌더링
        drawTetrisBoard();
        drawNextBlock();
        drawCurrentBlock();
        Sleep(20);
    }
}