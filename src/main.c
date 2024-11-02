#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game_of_life.h"

int main() {
    int rows, cols;
    get_terminal_size(&rows, &cols);

    int *grid = (int *)malloc(rows * cols * sizeof(int));
    int *new_grid = (int *)malloc(rows * cols * sizeof(int));
    int *prev_grid = (int *)malloc(rows * cols * sizeof(int));

    printf("\033[H\033[J"); // Clear the screen when the program starts
    initialize_grid(grid, rows, cols);

    while (1) {
        int new_rows, new_cols;
        get_terminal_size(&new_rows, &new_cols);

        if (new_rows != rows || new_cols != cols) {
            free(grid);
            free(new_grid);
            free(prev_grid);

            rows = new_rows;
            cols = new_cols;

            grid = (int *)malloc(rows * cols * sizeof(int));
            new_grid = (int *)malloc(rows * cols * sizeof(int));
            prev_grid = (int *)malloc(rows * cols * sizeof(int));

            initialize_grid(grid, rows, cols);
            printf("\033[H\033[J"); // Clear the screen only when the size changes
        }

        display_grid(grid, prev_grid, rows, cols);
        update_grid(grid, new_grid, rows, cols);

        // Swap grids
        int *temp = prev_grid;
        prev_grid = grid;
        grid = new_grid;
        new_grid = temp;

        usleep(100000); // Sleep for 100 milliseconds
    }

    free(grid);
    free(new_grid);
    free(prev_grid);

    return 0;
}
