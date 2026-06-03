#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

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

void playSnake();

#endif
