#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define WALL '#'
#define POINT '*'
#define BULI 'B'
#define BEAR 'D'

typedef struct {
    int x, y;
} Position;

char maze[SIZE][SIZE];
Position buli, bear;

void InitMaze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = POINT; // Default all positions to points
        }
    }
}

void PlaceWalls(int num_walls) {
    int x, y;
    for (int i = 1; i < num_walls+1; i++) {
        printf("Enter wall [%d]: ", i);
        scanf("%d %d", &x, &y);
        if (x < SIZE && y < SIZE)
        {
            maze[x][y] = WALL;
        }
        else
        {
            printf("invalid wall placment\n");
        }
    }
}

void SetStartPositions() {
    printf("\nEnter Buli's starting position (row column): ");
    scanf("%d %d", &buli.x, &buli.y);
    printf("Enter the Bear's starting position (row column): ");
    scanf("%d %d", &bear.x, &bear.y);
    maze[buli.x][buli.y] = BULI;
    maze[bear.x][bear.y] = BEAR;
}


void ClearConsole()
{
    printf("\033[H\033[J");
}

void PrintMaze() {
    
    ClearConsole();
    printf("1 - Move Right\n2 - Move Left\n3 - Move Up\n4 - Move Down\n0 - Continue previous move\n\n");
    printf("\n=========== MAZE ===========\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("============================\n");
}

int IsValidMove(int x, int y) {
    return x >= 0 && x < SIZE&& y >= 0 && y < SIZE&& maze[x][y] != WALL;
}

void MoveBuli(int direction) {
    static int last_move = 0; 
    if (direction != 0) last_move = direction;

    int new_x = buli.x, new_y = buli.y;
    switch (last_move) {
    case 1: new_y++; break; // Right
    case 2: new_y--; break; // Left
    case 3: new_x--; break; // Up
    case 4: new_x++; break; // Down
    }

    if (IsValidMove(new_x, new_y)) {
        maze[buli.x][buli.y] = ' ';
        buli.x = new_x;
        buli.y = new_y;
        maze[buli.x][buli.y] = BULI;
    }
    else {
        printf("\nBuli hit a wall! Try a different move.\n");
    }
}

void MoveBear() {
    int dx = (buli.x > bear.x) ? 1 : (buli.x < bear.x) ? -1 : 0;
    int dy = (buli.y > bear.y) ? 1 : (buli.y < bear.y) ? -1 : 0;

    static char prev_char = POINT;
    maze[bear.x][bear.y] = prev_char;  // Restore previous tile

    int new_x = bear.x + dx;
    int new_y = bear.y + dy;

    if (dx != 0 && dy != 0 && IsValidMove(new_x, new_y)) {
        bear.x = new_x;
        bear.y = new_y;
    }
    else if (dx != 0 && IsValidMove(new_x, bear.y)) {
        bear.x = new_x;
    }
    else if (dy != 0 && IsValidMove(bear.x, new_y)) {
        bear.y = new_y;
    }

    prev_char = (maze[bear.x][bear.y] == POINT) ? POINT : ' ';
    maze[bear.x][bear.y] = BEAR;
}



int main() {
    int num_walls;
    printf("Welcome to Buli's Maze Adventure!\n");
    printf("Enter number of walls: ");
    scanf("%d", &num_walls);

    InitMaze();
    PlaceWalls(num_walls);
    SetStartPositions();

    int move;
    printf("\nGame starts now! Guide Buli using these controls:\n");
    while (1) {
        PrintMaze();
        printf("Enter your move: ");
        scanf("%d", &move);
        MoveBuli(move);
        MoveBear();

        if (buli.x == bear.x && buli.y == bear.y) {
            printf("\nGame Over! The bear caught Buli!\n");
            break;
        }
    }
    return 0;
}

