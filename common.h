#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>

// 시스템 초기화
void initSystem();

// 좌표 이동
void gotoxy(int x, int y);

// 색상 변경
void setColor(int color);

// 커서 표시 여부
void setCursorVisible(int visible);

#endif