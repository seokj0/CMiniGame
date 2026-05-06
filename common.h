#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <stdio.h>

// 화면 크기 (50x30)
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 30

// 공통 기능 함수 선언
void initSystem();
void gotoxy(int x, int y);
void setColor(int color); 

#endif