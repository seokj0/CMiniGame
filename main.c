#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include "common.h" 

int main() {
    initSystem();

    gotoxy(11, 5);
    setColor(11);
    printf("==========================");
    
    gotoxy(18, 7);
    setColor(15);
    printf("C-MINI GAME");
    
    gotoxy(11, 9);
    setColor(11);
    printf("==========================");

    gotoxy(10, 15);
    setColor(14);
    printf("1. Omok  2. Tetris  3. Snake");

    gotoxy(10, 25);
    setColor(7);
    printf("Press Enter Key to Start...");

    getchar();
    return 0;
}