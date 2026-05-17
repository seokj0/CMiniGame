#include "common.h"
#include "tetris_model.h"

// 게임판 출력
void drawTetrisBoard() {

    int startX = 4;
    int startY = 2;

    // 세로
    for (int y = 0; y <= BOARD_HEIGHT; y++) {

        // 가로
        for (int x = 0; x <= BOARD_WIDTH + 1; x++) {

            gotoxy(startX + x * 2, startY + y);

            // 바닥
            if (y == BOARD_HEIGHT) {

                setColor(7);

                if (x == 0)
                    printf("+");

                else if (x == BOARD_WIDTH + 1)
                    printf("+");

                else
                    printf("--");
            }

            // 좌우 벽
            else if (x == 0 || x == BOARD_WIDTH + 1) {

                setColor(7);

                printf("||");
            }

            // 내부
            else {

                setColor(8);

                printf(". ");
            }
        }
    }

    // 블럭 미리보기
    int infoX = startX + (BOARD_WIDTH * 2) + 8;

    setColor(15);

    gotoxy(infoX, startY);
    printf("[ NEXT ]");

    gotoxy(infoX - 2, startY + 1);
    printf("+----------+");

    for (int i = 1; i <= 4; i++) {

        gotoxy(infoX - 2, startY + 1 + i);

        printf("|          |");
    }

    gotoxy(infoX - 2, startY + 6);

    printf("+----------+");

    // 조작 설명
    setColor(7);

    gotoxy(infoX, startY + 9);
    printf("  o    메인메뉴");

    gotoxy(infoX, startY + 11);
    printf("<- ->  이동");

    gotoxy(infoX, startY + 13);
    printf("  V    설치");

    gotoxy(infoX, startY + 15);
    printf("Space  회전");
}

// 다음 블록 출력
void drawNextBlock() {

    int startX = 4;
    int startY = 2;

    int boxInnerX = startX + (BOARD_WIDTH * 2) + 8;
    int boxInnerY = startY + 2;

    // 박스 내부 초기화
    for (int y = 0; y < 4; y++) {

        gotoxy(boxInnerX, boxInnerY + y);

        printf("        ");
    }

    // 블록 색상
    int blockColors[] = {
        11, 13, 14,
        9, 12, 10, 4
    };

    setColor(blockColors[g_nextBlockType]);

    // 블록 출력
    for (int y = 0; y < 4; y++) {

        gotoxy(boxInnerX, boxInnerY + y);

        for (int x = 0; x < 4; x++) {

            int isBlock =
                g_blocks[g_nextBlockType][y][x];

            if (isBlock == 1)
                printf("[]");

            else
                printf("  ");
        }
    }
}