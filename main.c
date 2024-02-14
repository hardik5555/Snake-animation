#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

int score = 0;
int gameover;
int x, y, fruitX, fruitY, flag;

// Function to generate random fruit position
void setup() {
    gameover = 0;

    // Initial position of the snake
    x = HEIGHT / 2;
    y = WIDTH / 2;

    // Generating initial fruit position
    fruitX = rand() % HEIGHT;
    if (fruitX == 0)
        fruitX++;
    fruitY = rand() % WIDTH;
    if (fruitY == 0)
        fruitY++;

    score = 0; // Reset score
}

// Function to draw the game board
void draw() {
    system("cls"); // Clear the console screen
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1) {
                // Draw border
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("0"); // Draw snake head
                else if (i == fruitX && j == fruitY)
                    printf("F"); // Draw fruit
                else
                    printf(" "); // Empty space
            }
        }
        printf("\n");
    }
    printf("Score: %d", score);
    printf("\n");
    printf("Press 'x' to quit the game");
}

// Function to take input from the user
void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                flag = 1; // Move left
                break;
            case 'd':
                flag = 2; // Move right
                break;
            case 'w':
                flag = 3; // Move up
                break;
            case 's':
                flag = 4; // Move down
                break;
            case 'x':
                gameover = 1; // Quit the game
                break;
        }
    }
}

// Function to update the game state
void algorithm() {
    Sleep(0.01); // Introducing a slight delay
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
        case 4:
            x++;
            break;
        default:
            break;
    }

    // Logic for collision with walls
    if (x < 0 || x > HEIGHT || y < 0 || y > WIDTH)
        gameover = 1;

    // Logic for collision with fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % HEIGHT;
        if (fruitX == 0)
            fruitX++;
        fruitY = rand() % WIDTH;
        if (fruitY == 0)
            fruitY++;
    }

    // Logic for snake body
    for (int i = 0; i < score; i++) {
        prev2X = prevX;
        prev2Y = prevY;
        prevX = x;
        prevY = y;
        if (i == 0) {
            x = prev2X;
            y = prev2Y;
        }
    }
}

int main() {
    int m, n;

    setup();
    while (!gameover) {
        draw();
        input();
        algorithm();
    }
    return 0;
}
