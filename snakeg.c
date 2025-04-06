#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
char direction;

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor information
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Set the cursor visibility to false
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void setup() {
    gameOver = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    direction = RIGHT;

    // Hide the cursor
    hideCursor();
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);
}

void draw() {
    clearScreen(); // Replace system("cls") with this function
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case UP:
            if (direction != DOWN)
                direction = UP;
            break;
        case DOWN:
            if (direction != UP)
                direction = DOWN;
            break;
        case LEFT:
            if (direction != RIGHT)
                direction = LEFT;
            break;
        case RIGHT:
            if (direction != LEFT)
                direction = RIGHT;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
    case UP:
        y--;
        delay(40); // Adjust delay for vertical movement
        break;
    case DOWN:
        y++;
        delay(40); // Adjust delay for vertical movement
        break;
    case LEFT:
        x--;
        delay(30); // Adjust delay for horizontal movement
        break;
    case RIGHT:
        x++;
        delay(30); // Adjust delay for horizontal movement
        break;
    }

    if (x >= WIDTH) x = 0;
    else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0;
    else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}



int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        
    }
    printf("Game Over!\n");
    return 0;
}
