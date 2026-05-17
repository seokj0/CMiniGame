#include "common.h"
#include "tetris_model.h"
#include <stdlib.h>
#include <time.h>

// 1. 게임판 배열 생성
int g_board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

// 블럭 데이터
int g_blocks[7][4][4] = {

    // 0: I 모양
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 1: T 모양
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 2: O 모양
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 3: J 모양
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 4: L 모양
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 5: S 모양
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // 6: Z 모양
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

int g_currentBlockType = 0;
int g_nextBlockType = 0;

// 함수 선언
void drawTetrisBoard();
void drawNextBlock();

void playTetris() {
    // 랜덤 시드 초기화 (매번 다른 블록이 나오도록 함)
    srand((unsigned int)time(NULL));

    // 최초 블록 세팅 (현재 블록과 다음 블록을 랜덤으로 뽑음)
    g_currentBlockType = rand() % 7;
    g_nextBlockType = rand() % 7;

    system("cls");
    drawTetrisBoard(); // 테두리 그리기
    drawNextBlock();   // 미리보기 칸에 다음 블록 그리기

    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 'o') break;

            // 스페이스바 누르면 다음 블록이 갱신 (테스트용)
            if (key == ' ') {
                g_currentBlockType = g_nextBlockType;
                g_nextBlockType = rand() % 7;
                drawNextBlock();
            }
        }
        Sleep(100);
    }
}