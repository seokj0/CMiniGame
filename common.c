#include "common.h"

void initSystem() {
    // 1. 한글 깨짐 방지 및 화면 초기화
    system("chcp 65001");
    system("cls");

    // 2. 콘솔 창 제목 및 크기 설정
    system("title C-Mini Game World");
    system("mode con cols=50 lines=30");

    // 3. 커서 숨기기
    setCursorVisible(0);

    // 4. 마우스 클릭 시 멈춤 방지
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setCursorVisible(int visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 10;
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}