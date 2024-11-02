#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

void initialize_grid(int *grid, int rows, int cols);
void display_grid(int *grid, int *prev_grid, int rows, int cols);
void update_grid(int *grid, int *new_grid, int rows, int cols);
void get_terminal_size(int *rows, int *cols);

#endif
