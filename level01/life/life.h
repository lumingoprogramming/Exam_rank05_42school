#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h> // malloc, free, atoi
#include <unistd.h> // read, write

char **alloc_board(int w, int h);

void free_board(char **b,  int h);

void draw_initial(char **b, int w, int h);

void play(char **b, int w, int h);

void print_board(char **b, int w, int h);

#endif