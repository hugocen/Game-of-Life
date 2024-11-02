#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "game_of_life.h"

void get_terminal_size(int *rows, int *cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
}

void initialize_grid(int *grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i * cols + j] = rand() % 10 < 1; // Approximately 10% chance of being alive
        }
    }
}

void display_grid(int *grid, int *prev_grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i * cols + j] != prev_grid[i * cols + j]) {
                printf("\033[%d;%dH", i + 1, j + 1); // Move cursor to the position
                printf(grid[i * cols + j] ? "\u2588" : " ");
            }
        }
    }
    fflush(stdout);
}

void update_grid(int *grid, int *new_grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int live_neighbors = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        live_neighbors += grid[ni * cols + nj];
                    }
                }
            }
            if (grid[i * cols + j] && (live_neighbors == 2 || live_neighbors == 3)) {
                new_grid[i * cols + j] = 1;
            } else if (!grid[i * cols + j] && live_neighbors == 3) {
                new_grid[i * cols + j] = 1;
            } else {
                new_grid[i * cols + j] = 0;
            }
        }
    }
}