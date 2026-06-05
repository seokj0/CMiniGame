#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define MAP_SIZE 22

#define WALL 1
#define EMPTY 0
#define HEAD 2
#define TAIL 3
#define FRUIT 5
#define COLLISION 10

#define TRUE 1
#define FALSE 0

#define NORMAL 10

typedef int MData;

typedef struct _fruitxy {
    int x;
    int y;
    int numOfFruit;
} FruitPos;

typedef struct _snakexp {
    int x;
    int y;
} SnakePos;

typedef struct _mynode {
    SnakePos data;
    struct _mynode* next;
} Node;

typedef struct _myqueue {
    Node* rear;
    Node* front;
} MyQueue;

typedef MyQueue Queue;

void QueueInit(Queue* pq) {
    pq->rear = NULL;
    pq->front = NULL;
}

int isEmpty(Queue* pq) {
    if (pq->front == NULL)
        return TRUE;
    else
        return FALSE;
}

void Enqueue(Queue* pq, SnakePos data) {

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if (pq->front == NULL) {
        pq->rear = newNode;
        pq->front = newNode;
    }
    else {
        pq->rear->next = newNode;
        pq->rear = newNode;
    }
}

SnakePos Dequeue(Queue* pq) {

    Node* delNode;

    SnakePos delData = { 0, 0 };

    if (isEmpty(pq)) {
        return delData;
    }

    delNode = pq->front;

    delData = delNode->data;

    pq->front = pq->front->next;

    free(delNode);

    return delData;
}

int getKeyDown() {

    if (_kbhit())
        return _getch();

    return -1;
}

void snake_gotoxy(int x, int y) {
    COORD Pos;
    
    Pos.X = 2 * x;
    Pos.Y = y; 
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void hidecursor() {

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = FALSE;

    SetConsoleCursorInfo(consoleHandle, &info);
}



int drawStartMenu() {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hand, 13);

    snake_gotoxy(DEFAULT_X, DEFAULT_Y);
    printf("============================================");

    SetConsoleTextAttribute(hand, 14);

    snake_gotoxy(DEFAULT_X, DEFAULT_Y + 1);
    printf("================ Snake Game ================");

    SetConsoleTextAttribute(hand, 11);

    snake_gotoxy(DEFAULT_X, DEFAULT_Y + 2);
    printf("============================================");

    SetConsoleTextAttribute(hand, 15);

    snake_gotoxy(DEFAULT_X, DEFAULT_Y + 4);
    printf("> Key  : up, down, left, right");

    snake_gotoxy(DEFAULT_X, DEFAULT_Y + 5);
    printf("> Start : 's'");

    snake_gotoxy(DEFAULT_X, DEFAULT_Y + 6);
    printf("> Exit : 'o'");

    SetConsoleTextAttribute(hand, 14);

    while (1) {

        int keyDown = getKeyDown();

        if (keyDown == 's' || keyDown == 'S') {

            SetConsoleTextAttribute(hand, 7);

            return TRUE;
        }

        if (keyDown == 'o' || keyDown == 'O') {

            SetConsoleTextAttribute(hand, 7);

            return FALSE;
        }

        snake_gotoxy(DEFAULT_X + 5, DEFAULT_Y + 10);
        printf("-- press 's' to start --");

        Sleep(1000 / 3);

        snake_gotoxy(DEFAULT_X + 5, DEFAULT_Y + 10);
        printf("                           ");

        Sleep(1000 / 3);
    }
}

void stageOneInit(MData map[MAP_SIZE][MAP_SIZE]) {

    int i, j;

    for (i = 0; i < MAP_SIZE; i++) {

        if (i == 0 || i == MAP_SIZE - 1) {

            for (j = 0; j < MAP_SIZE; j++) {
                map[i][j] = WALL;
            }
        }
        else {

            for (j = 0; j < MAP_SIZE; j++) {

                if (j == 0 || j == MAP_SIZE - 1)
                    map[i][j] = WALL;
                else
                    map[i][j] = EMPTY;
            }
        }
    }
}

void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]) {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    int i, j;

    SetConsoleTextAttribute(hand, 15);

    for (i = 0; i < MAP_SIZE; i++) {

        for (j = 0; j < MAP_SIZE; j++) {

            if (map[i][j] == WALL) {

                snake_gotoxy(i, j);
                printf("#");
            }
            else if (map[i][j] == EMPTY) {

                snake_gotoxy(i, j);
                printf(" ");
            }
        }
    }

    SetConsoleTextAttribute(hand, 7);
}

void drawSubMap(int score, int best) {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hand, 15);

    snake_gotoxy(DEFAULT_X, MAP_SIZE + 1);
    printf(" Best Score : %4d", best);

    snake_gotoxy(DEFAULT_X, MAP_SIZE + 2);
    printf(" Your Score : %4d", score);

    snake_gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
    printf("[Exit - 'o' / Pause - 'p']");

    SetConsoleTextAttribute(hand, 7);
}

int setFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos* fp) {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    int i, j;

    while (1) {

        i = rand() % (MAP_SIZE - 2) + 1;
        j = rand() % (MAP_SIZE - 2) + 1;

        if (map[i][j] == EMPTY) {

            map[i][j] = FRUIT;

            fp->x = i;
            fp->y = j;

            fp->numOfFruit++;

            SetConsoleTextAttribute(hand, 10);

            snake_gotoxy(i, j);
            printf("*");

            SetConsoleTextAttribute(hand, 7);

            return 1;
        }
    }
}

void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hand, 14);

    snake_gotoxy(snake_x, snake_y);

    printf("0");

    map[snake_x][snake_y] = TAIL;

    SetConsoleTextAttribute(hand, 7);
}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    snake_gotoxy(snake_x, snake_y);

    SetConsoleTextAttribute(hand, 14);

    printf("@");

    SetConsoleTextAttribute(hand, 7);

    map[snake_x][snake_y] = HEAD;
}

void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {

    snake_gotoxy(snake_x, snake_y);

    printf(" ");

    map[snake_x][snake_y] = EMPTY;
}

int colWithTail(MData map[MAP_SIZE][MAP_SIZE], SnakePos* sp, int way) {

    if (way == UP) {

        if (map[sp->x][sp->y - 1] == TAIL)
            return TRUE;
    }

    if (way == DOWN) {

        if (map[sp->x][sp->y + 1] == TAIL)
            return TRUE;
    }

    if (way == LEFT) {

        if (map[sp->x - 1][sp->y] == TAIL)
            return TRUE;
    }

    if (way == RIGHT) {

        if (map[sp->x + 1][sp->y] == TAIL)
            return TRUE;
    }

    return FALSE;
}

int colWithWall(MData map[MAP_SIZE][MAP_SIZE], SnakePos* sp, int way) {

    if (way == UP) {

        if (map[sp->x][sp->y - 1] == WALL)
            return TRUE;
    }

    if (way == DOWN) {

        if (map[sp->x][sp->y + 1] == WALL)
            return TRUE;
    }

    if (way == LEFT) {

        if (map[sp->x - 1][sp->y] == WALL)
            return TRUE;
    }

    if (way == RIGHT) {

        if (map[sp->x + 1][sp->y] == WALL)
            return TRUE;
    }

    return FALSE;
}

int moveSnakeHead(MData map[MAP_SIZE][MAP_SIZE], SnakePos* snake, int way) {

    removeSnake(map, snake->x, snake->y);

    if (colWithWall(map, snake, way) == TRUE) {

        snake_gotoxy(1, 1);

        printf("> Hit : wall");

        return COLLISION;
    }

    if (colWithTail(map, snake, way) == TRUE) {

        snake_gotoxy(1, 1);

        printf("> Hit : tail");

        return COLLISION;
    }

    if (way == UP) {

        snake->y--;

        setSnake(map, snake->x, snake->y);

        return UP;
    }

    if (way == DOWN) {

        snake->y++;

        setSnake(map, snake->x, snake->y);

        return DOWN;
    }

    if (way == LEFT) {

        snake->x--;

        setSnake(map, snake->x, snake->y);

        return LEFT;
    }

    if (way == RIGHT) {

        snake->x++;

        setSnake(map, snake->x, snake->y);

        return RIGHT;
    }

    return way;
}

int overlap(int savedKey, int key) {

    if (savedKey == UP && key == DOWN)
        return TRUE;

    if (savedKey == DOWN && key == UP)
        return TRUE;

    if (savedKey == LEFT && key == RIGHT)
        return TRUE;

    if (savedKey == RIGHT && key == LEFT)
        return TRUE;

    return FALSE;
}

int colWithFruit(SnakePos* sp, FruitPos* fp) {

    if (sp->x == fp->x && sp->y == fp->y)
        return TRUE;

    return FALSE;
}

int isCollision(int state) {

    if (state == COLLISION)
        return TRUE;

    return FALSE;
}

void GameOver(int score, int best, Queue* pq, int* scoreArr) {

    FILE* wfp;

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    if (score >= best)
        scoreArr[0] = score;
    else
        scoreArr[0] = best;

    wfp = fopen("score.txt", "w");

    fprintf(wfp, "%d", scoreArr[0]);

    fclose(wfp);

    SetConsoleTextAttribute(hand, 14);

    snake_gotoxy(MAP_SIZE / 2 - 4, MAP_SIZE / 2 - 5);

    printf("===<GAME OVER>===");

    snake_gotoxy(MAP_SIZE / 2 - 3, MAP_SIZE / 2 - 3);

    printf("Your Score : %d", score);

    snake_gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);

    printf("                    ");

    SetConsoleTextAttribute(hand, 7);

    while (!isEmpty(pq)) {
        Dequeue(pq);
    }
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE], int* scoreArr) {

    int best = scoreArr[0];
    int score = 0;
    int key;
    int savedKey = RIGHT;
    Queue queue;
    QueueInit(&queue);
    SnakePos snake = { MAP_SIZE / 4 - 2, MAP_SIZE / 4 + 1 };
    SnakePos snakeSecond;
    SnakePos snakeTail;
    int time = FALSE;
    FruitPos fruit;
    fruit.numOfFruit = 0;
    stageOneInit(map);
    drawMainMap(map);
    setSnake(map, snake.x, snake.y);
    while (1) {
        Sleep(1000 / (DWORD)NORMAL);
        if (fruit.numOfFruit == 0) {
            setFruit(map, &fruit);
        }
        drawSubMap(score, best);
        if (colWithFruit(&snake, &fruit) == TRUE) {
            fruit.numOfFruit--;
            time = FALSE;
            score += 5;
        }

        if (_kbhit()) {

            key = _getch();
            if (key == 'o' || key == 'O') {
                return;
            }
            if (key == 'p' || key == 'P') {

                system("pause");

                snake_gotoxy(DEFAULT_X, MAP_SIZE + 6);

                printf("                                            ");

                snake_gotoxy(DEFAULT_X, DEFAULT_Y);
            }

            if (key == 224 || key == 0) {

                key = _getch();

                if (overlap(savedKey, key) == TRUE) {
                    key = savedKey;
                }

                snakeSecond = snake;

                savedKey = moveSnakeHead(map, &snake, key);

                Enqueue(&queue, snakeSecond);

                setSnakeTail(map, snakeSecond.x, snakeSecond.y);

                if (time == TRUE) {

                    snakeTail = Dequeue(&queue);

                    removeSnake(map, snakeTail.x, snakeTail.y);
                }
                else {
                    time = TRUE;
                }

                if (isCollision(savedKey)) {

                    GameOver(score, best, &queue, scoreArr);

                    return;
                }
            }
        }
        else {

            snakeSecond = snake;

            savedKey = moveSnakeHead(map, &snake, savedKey);

            Enqueue(&queue, snakeSecond);

            setSnakeTail(map, snakeSecond.x, snakeSecond.y);

            if (time == TRUE) {

                snakeTail = Dequeue(&queue);

                removeSnake(map, snakeTail.x, snakeTail.y);
            }
            else {
                time = TRUE;
            }


            if (isCollision(savedKey)) {
                
                GameOver(score, best, &queue, scoreArr);

                return;
            }
        }
    }
}

void playSnake() {

    MData map[MAP_SIZE][MAP_SIZE];

    int scoreArr[1] = { 0 };

      srand((unsigned int)time(NULL));

    system("color 7");

    system("mode con: cols=50 lines=30");

    setCursorVisible(0);

    while (1) {

        if (drawStartMenu() == FALSE)
            break;

        system("cls");

        GameStart(map, scoreArr);

        system("pause");

        system("cls");
    }
}
