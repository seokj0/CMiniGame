#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>

// 시스템 초기화 (콘솔 크기, 커서 숨기기)
void initSystem();

// 화면 좌표 이동 함수
void gotoxy(int x, int y);

// 텍스트 색상 변경 함수
void setColor(int color);

// 커서 보이기/숨기기 설정
void setCursorVisible(int visible);

#endif