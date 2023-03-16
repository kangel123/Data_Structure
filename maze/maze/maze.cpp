#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <Windows.h>

#define m 12
#define p 12
#define Max_dir  8
#define Timestep 1000

typedef struct Aoff {
    short int vert;
    short int horiz;
} offsets;

typedef struct  St_element {
    short int row;
    short int col;
    short int dir;
} ty_element;

typedef struct ListNode* listPointer;
typedef struct ListNode {
    ty_element data;
    listPointer link;
} listNode;

offsets move[Max_dir] = { {-1,0}, {-1,1},  {0,1},  {1,1},   {1,0},  {1,-1},  {0,-1}, {-1,-1} };

int maze[m + 2][p + 2];
int mark[m + 2][p + 2];

void gotoxy(int x, int y){
    COORD Pos = { x ,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void push(listPointer* top, ty_element num) {
    listNode* temp;
    temp = (listNode*)malloc(sizeof(listNode));
    temp->data = num;
    temp->link = *top;
    *top = temp;
}

ty_element pop(listPointer* top) {
    listPointer temp = *top;
    ty_element num = temp->data;
    *top = temp->link;
    free(temp);
    return num;
}

void reverse(listPointer* top) {
    listNode* a, * b, * c;
    a = *top;
    b = NULL;
    while (a != NULL) {
        c = b;
        b = a;
        a = a->link;
        b->link = c;

    }
    *top = b;
}

int path(int sy, int sx, int dy, int dx){
    listPointer top = NULL;
    int i, j, row, col, nextRow, nextCol, dir, basex, basey, ocount;
    int found, num_bktrack = 0, path_length = 0;
    int EXIT_ROW = dy, EXIT_COL = dx;
    ty_element position;

    if (maze[sy][sx] == 1 || maze[dy][dx] == 1) {
        printf("입력오류: 출발점이나 목표점이 막힌 셀입니다.\n\n");
        return 0;
    }

    CONSOLE_SCREEN_BUFFER_INFO presentCur;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
    basex = presentCur.dwCursorPosition.X;
    basey = presentCur.dwCursorPosition.Y;

    for (i = 0; i < m + 2; i++) {
        for (j = 0; j < p + 2; j++) {
            gotoxy(j + basex, i + basey);
            printf("%1d", maze[i][j]);
        }
    }

    position.row = sy;  position.col = sx;   position.dir = 0;
    push(&top, position);

    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            mark[1 + i][1 + j] = 0;
        }
    }
    mark[sy][sx] = 1;
    gotoxy(sx + basex, sy + basey);
    printf(">"); 
    Sleep(Timestep);

    found = FALSE;
    while(top !=NULL && !found) {
        position = pop(&top);
        row = position.row; col = position.col; dir = position.dir;

        while (dir < Max_dir && !found) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
                found = TRUE;
                gotoxy(nextCol + basex, nextRow + basey);
                printf("<");
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                position.row = row; position.col = col; position.dir = ++dir;
                push(&top, position);
                row = nextRow; col = nextCol;
                gotoxy(col + basex, row + basey);
                printf("*");
                Sleep(Timestep);
                dir = 0;
                mark[row][col] = 1;
                
            }
            else
                ++dir;
        }
        if (found)
            break;
       
        gotoxy(col + basex, row + basey);
        printf("%c", '$');
        num_bktrack++;
        Sleep(Timestep);
    }

        gotoxy(0, basey + m + 3);
        if (found) {
            reverse(&top);
            printf("찾은 경로(row,col):");
            ocount = 0;
            while (top)
            {
                position = top->data;
                printf("[%2d, %2d] ", position.row, position.col);
                ocount++;
                top = top->link;

            }
            printf("[%2d, %2d] ", row, col);
            printf("[%2d, %2d]\n\n", EXIT_ROW, EXIT_COL);
            
            path_length = ocount + 2;
            printf("경로길이= %d,  백트래킹수= %d\n\n", path_length, num_bktrack);
        }
        else
            printf("가능 경로가 없음.\n");
        return FALSE;
    }



void main() {
    int i, j, res;
    int starty, startx, endy, endx;
    FILE* fp;
    if ((fp = fopen("maze_14_2.txt", "r")) == NULL) {
        printf("파일열기 실패\n");
        getchar();
    }

    for (i = 0; i < m + 2; i++) {
        for (j = 0; j < p + 2; j++) {
            res = fscanf(fp, "%d", &maze[i][j]);
            if (res != 1) {
                printf("화일에서 maze 읽기 실패.\n");
                getchar();
            }
        }
    }

    while (1) {
        printf("출발점, 목표점은?(4개의 정수; 종료는 Control+D Enter): ");
        res = scanf("%d%d%d%d", &starty, &startx, &endy, &endx);
        if (res != 4) break;
        path(starty, startx, endy, endx);
    }

}
