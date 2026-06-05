#define _CRT_SECURE_NO_WARNINGS
#include "common.h"

extern void playTetris();
extern void playOmok();
extern void playSnake();

// 1: 테트리스, 2: 오목, 3: 스네이크, 0: 종료
int g_selectedMenu = 1;

// 메뉴 화면을 그리는 함수
void drawMenu() {
    system("cls"); // 화면 지우기

    // 타이틀 영역
    gotoxy(10, 5);
    setColor(11); // 하늘색
    printf("==============================");
    gotoxy(16, 7);
    setColor(15); // 흰색
    printf("C-MINI GAME WORLD");
    gotoxy(10, 9);
    setColor(11);
    printf("==============================");

    // g_selectedMenu 값에 따라 강조 표시
    // 1. Tetris
    gotoxy(18, 13);
    if (g_selectedMenu == 1) {
        setColor(14); // 노란색
        printf("> 1. Tetris <");
    }
    else {
        setColor(7); // 일반 회색
        printf("  1. Tetris  ");
    }

    // 2. Omok
    gotoxy(18, 15);
    if (g_selectedMenu == 2) {
        setColor(14);
        printf("> 2. Omok   <");
    }
    else {
        setColor(7);
        printf("  2. Omok    ");
    }

    // 3. Snake
    gotoxy(18, 17);
    if (g_selectedMenu == 3) {
        setColor(14);
        printf("> 3. Snake  <");
    }
    else {
        setColor(7);
        printf("  3. Snake   ");
    }

    // 0. Exit
    gotoxy(18, 20);
    if (g_selectedMenu == 0) {
        setColor(12); // 빨간색
        printf("> 0. Exit   <");
    }
    else {
        setColor(7);
        printf("  0. Exit    ");
    }

    gotoxy(12, 25);
    setColor(8); // 어두운 회색
    printf("Use Arrow Keys & Press Enter");
}

int main() {
    // 시스템 초기화
    initSystem();

    while (1) {
        drawMenu(); // 메뉴 화면 출력

        int key = _getch();
        // (아스키 코드, 확장 키 코드)
        // 1. 방향키 처리
        if (key == 224) {
            key = _getch(); // 실제 방향키 값 확인
            switch (key) {
            case 72: // 위쪽 방향키
                g_selectedMenu--;
                if (g_selectedMenu < 0) g_selectedMenu = 3; // 0 아래로 가면 3번으로 순환
                break;
            case 80: // 아래쪽 방향키
                g_selectedMenu++;
                if (g_selectedMenu > 3) g_selectedMenu = 0; // 3 위로 가면 0번으로 순환
                break;
            }
        }
        // 2. 엔터키 처리
        else if (key == 13) {
            if (g_selectedMenu == 0) break; // 종료 선택시 루프 탈출

            // 각 게임으로 진입 전 연출
            system("cls");
            gotoxy(15, 14);
            setColor(15);

            if (g_selectedMenu == 1) {
                printf("Entering Tetris World...");
                Sleep(800);

                playTetris();
            }
            else if (g_selectedMenu == 2) {
                printf("Entering Omok World...");
                Sleep(800);

                playOmok();
            }
            else if (g_selectedMenu == 3) {
                printf("Entering Snake World...");
                Sleep(800);

                playSnake();
            }
        }
    }

    // 종료 화면
    system("cls");
    printf("C-Mini Game World를 종료합니다.\n");
    return 0;
}