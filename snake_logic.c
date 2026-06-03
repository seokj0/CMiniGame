#include "snake_model.h"
#include "common.h"

void QueueInit(Queue* pq) {

    pq->rear = NULL;
    pq->front = NULL;
}

int isEmpty(Queue* pq) {

    if (pq->front == NULL)
        return TRUE;

    return FALSE;
}

void Enqueue(Queue* pq, SnakePos data) {

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if (pq->front == NULL) {
        pq->front = newNode;
        pq->rear = newNode;
    }
    else {
        pq->rear->next = newNode;
        pq->rear = newNode;
    }
}

SnakePos Dequeue(Queue* pq) {

    Node* delNode;
    SnakePos delData = { 0,0 };
    delNode = pq->front;
    delData = delNode->data;
    pq->front = pq->front->next;
    free(delNode);

    return delData;
}

void stageOneInit(MData map[MAP_SIZE][MAP_SIZE]) {

    int i, j;

    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {

            if (i == 0 || j == 0 ||
                i == MAP_SIZE - 1 ||
                j == MAP_SIZE - 1)
                map[i][j] = WALL;
            else
                map[i][j] = EMPTY;
        }
    }
}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int x, int y) {

    gotoxy(x * 2, y);
    printf("@");

    map[x][y] = HEAD;
}

void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int x, int y) {

    gotoxy(x * 2, y);
    printf(" ");

    map[x][y] = EMPTY;
}

int moveSnakeHead(MData map[MAP_SIZE][MAP_SIZE], SnakePos* snake, int way) {

    removeSnake(map, snake->x, snake->y);

    if (way == UP)
        snake->y--;

    if (way == DOWN)
        snake->y++;

    if (way == LEFT)
        snake->x--;

    if (way == RIGHT)
        snake->x++;

    if (map[snake->x][snake->y] == WALL)
        return COLLISION;

    setSnake(map, snake->x, snake->y);

    return way;
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {

    int key;
    int savedKey = RIGHT;

    SnakePos snake = { 5,5 };

    stageOneInit(map);
    drawMainMap(map);
    setSnake(map, snake.x, snake.y);

    while (1) {

        Sleep(1000 / NORMAL);
        if (_kbhit()) {
            key = _getch();
            if (key == 224)
                key = _getch();
            savedKey = key;
        }

        if (moveSnakeHead(map, &snake, savedKey) == COLLISION) {

            gotoxy(10, 15);
            printf("GAME OVER");

            break;
        }
    }
}

void playSnake() {

    MData map[MAP_SIZE][MAP_SIZE];

    if (drawStartMenu() == FALSE)
        return;

    system("cls");

    GameStart(map);

    system("pause");
}
