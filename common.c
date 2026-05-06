#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "common.h"

// 콘솔 초기 설정
void initSystem() {
    // 1. 화면 크기 설정(50x30)
    char command[50];
    sprintf(command, "mode con: cols=%d lines=%d", SCREEN_WIDTH, SCREEN_HEIGHT);
    system(command);

    // 2. 커서 숨기기
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// 커서 이동 함수
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(consoleHandle, pos);
}

// 색상 변경 함수
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}