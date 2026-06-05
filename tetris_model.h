#ifndef TETRIS_MODEL_H
#define TETRIS_MODEL_H

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

// 7종의 4x4 크기 블럭 데이터(3차원 배열)
extern int g_blocks[7][4][4];

// 게임판 데이터
extern int g_board[BOARD_HEIGHT][BOARD_WIDTH];

// 현재 블럭과 다음 블럭의 종류
extern int g_currentBlockType;
extern int g_nextBlockType;

// 전역 변수들의 통로 개방
extern int g_blockX;
extern int g_blockY;
extern int g_currentRotation;

#endif