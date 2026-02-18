#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int WIDTH = 200;    // Terminal width
const int HEIGHT = 80;   // Terminal height
const int NUM_STREAMS = 30;  // Number of falling columns

// Move cursor to (x, y)
void moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

// Clear screen
void clearScreen() {
    cout << "\033[2J";
}

// Hide cursor
void hideCursor() {
    cout << "\033[?25l";
}

// Show cursor
void showCursor() {
    cout << "\033[?25h";
}

int main() {
    srand(time(0));

    vector<int> columnPositions(NUM_STREAMS);

    // Random starting positions
    for (int i = 0; i < NUM_STREAMS; i++) {
        columnPositions[i] = rand() % HEIGHT;
    }

    clearScreen();
    hideCursor();

    while (true) {
        for (int i = 0; i < NUM_STREAMS; i++) {
            int column = rand() % WIDTH;
            int row = columnPositions[i];

            // Bright green head
            moveCursor(column, row);
            cout << "\033[1;32m" << (rand() % 2) << "\033[0m";

            // Dim green trail
            if (row > 2) {
                moveCursor(column, row - 2);
                cout << "\033[2;32m" << (rand() % 2) << "\033[0m";
            }

            // Erase tail
            if (row > 4) {
                moveCursor(column, row - 4);
                cout << " ";
            }

            columnPositions[i]++;

            if (columnPositions[i] > HEIGHT) {
                columnPositions[i] = 0;
            }
        }

        usleep(50000); // Speed control
    }

    showCursor();
    return 0;
}