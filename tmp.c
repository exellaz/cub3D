#include <stdio.h>

#define ROWS 5
#define COLS 5

void floodFill(int screen[ROWS][COLS], int x, int y, int prevC, int newC) {
    // Base cases
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) return;
    if (screen[x][y] != prevC) return;

    // Replace the color at (x, y)
    screen[x][y] = newC;

    // Recur for north, south, east, and west
    floodFill(screen, x + 1, y, prevC, newC);
    floodFill(screen, x - 1, y, prevC, newC);
    floodFill(screen, x, y + 1, prevC, newC);
    floodFill(screen, x, y - 1, prevC, newC);
}

void printScreen(int screen[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int screen[ROWS][COLS] = {
        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    int x = 1, y = 2; // Starting point
    int newC = 2; // New color to fill
    int prevC = screen[x][y]; // Previous color

    printf("Original screen:\n");
    printScreen(screen);

    floodFill(screen, x, y, prevC, newC);

    printf("\nScreen after flood fill:\n");
    printScreen(screen);

    return 0;
}
