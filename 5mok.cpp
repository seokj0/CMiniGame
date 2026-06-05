#include<stdio.h>
#include<Windows.h>
#include<conio.h>   //getchar
#include<string.h>
#include<locale.h>

#define MAX_N 19
#define DRAW_BLACK printf("○")
#define DRAW_WHITE printf("●")
#define WHITE 2
#define BLACK 1

void gotoxy(int x, int y);

int board[MAX_N][MAX_N] = { 0 };

void drawInit();
int drawStone(int y, int x, int stone);
void inputCode(int *y, int *x);
int checkFinish(int t);
void gotoInput();

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");


	CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // bVIsible과 dwSize를 구조체 변수로 가지는 구조체를 0으로 초기화.
	cursorInfo.bVisible = 0;   //bVisible = 커서 표시,숨김  False(0) = 숨김,   True (1) = 보임
	cursorInfo.dwSize = 1;     // dwSize = 커서 크기 (1~100)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // SetConsoleCursorInfo(콘솔핸들, 커서정보주소);    커서정보를 window.h의 구조체로 받음.

	drawInit();  // 오목판 출력
	int x, y, i = 1;
	for (;;) { // 무한반복
		inputCode(&y, &x);
		i += drawStone(y, x, (i) % 2 + 1);    //drawStone이 성공 시 1 반환. 성공시 i+=1, 실패시 i+=0, 
		if (int c = checkFinish(0)) {
			gotoInput();
			printf("GAME OVER.. ");
			if (c == WHITE)
				printf("WHITE "), DRAW_WHITE;
			else if (c == BLACK)
				printf("BLACK "), DRAW_BLACK;
			printf(" WIN!!! ");
			break;
		}
	}

	_getch();
	return 0;
}

int checkFinish(int t) {   //매개변수 t = 0으로 입력받음, 0~19^2까지 검사
	if (t == MAX_N * MAX_N)  // 
		return 0;
	int x = t % MAX_N;  //t를 19로 나눈 나머지로 x좌표 
	int y = t / MAX_N;  //t를 19로 나눈 몫으로 y좌표
	int color = board[y][x]; // color에 현재 색의 상태(1,2) 저장
	int dir[3] = { 0 };    // dir[0]은 가로, 1은 세로, 2는 대각. dir[n]=5일시 승리
	for (int i = 0; i < 5 && color != 0; i++) {  // and(논리곱)
		if (x + i < MAX_N && color == board[y][x + i])
			dir[0]++;
		if (y + i < MAX_N && color == board[y + i][x])
			dir[1]++;
		if (x + i < MAX_N && y + i < MAX_N && color == board[y + i][x + i])
			dir[2]++;
	}
	for (int i = 0; i < 3; i++)
		if (dir[i] == 5)
			return color;
	return checkFinish(t + 1);
}

void inputCode(int* y, int* x) {
	gotoInput(); // 21,10으로 이동
	printf("Input Coordinate (A19): ");
	char s[10];
	gets_s(s, sizeof(s));
	*x = s[0] - 'A';
	if (strlen(s) > 3) // strlen 은 <String.h> 헤더에 포함되어 있음.
		return ;  //범위(3)을 벗어난 입력을 받으면 return;
	if (strlen(s) == 3)  //y좌표가 2자리인 경우.
		*y = (s[1] - '0') * 10 + s[2] - '0' - 1;   // (s[1] - '0')
	else if (strlen(s) == 2)
		*y = s[1] - '0' - 1;
	else
		*y = *x = -1;
	gotoInput(); printf("Input Coordinate (A19): \t\t\t");   //입력이 끝난 후 새로고침용 출력
	return;
}

int drawStone(int y, int x, int stone) { // stone이 1이면 흑, 2면 백 오류시 0 반환
	if (board[y][x] || x<0 || x>=MAX_N || y<0 || y>=MAX_N) // ||논리합(or),  board[x][y]에 값이 있으면 0(false)가 아니므로 True.
		return 0;
	gotoxy(x, y);
	if (stone == BLACK) {
		DRAW_BLACK; 
		board[y][x] = BLACK;
	}
	else if (stone == WHITE) {
		DRAW_WHITE;
		board[y][x] = WHITE;
	}
	else
		return 0;
	return 1;
}

void drawInit() {
	gotoxy(0, 0);
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			gotoxy(j, i);               //i = 세로 / j = 가로
			if (i == 0) {
				if (j == 0)
					printf("┌");
				else if (j == MAX_N - 1)
					printf("┐");
				else
					printf("┬");
			}
			else if (j == 0) {
				if (i == MAX_N - 1)
					printf("└");
				else
					printf("├");
			}
			else if (j == MAX_N - 1) {
				if (i == MAX_N - 1)
					printf("┘");
				else
					printf("┤");
			}
			else if (i == MAX_N - 1) {
				printf("┴");
			}
			else
				printf("┼");
		}
		printf("\n");
	}
	for (int i = 0; i < MAX_N; i++) {
		gotoxy(MAX_N, i);
		printf("%d", i + 1);
		gotoxy(i, MAX_N);
		printf("%c", i + 'A');
	}
	gotoInput();
	printf("fin.");
}

void gotoxy(int x, int y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoInput() {
	gotoxy(21, 20);
}
 