#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>

typedef struct s_bsq {
    char **grid;
    int *dp;
    int rows, cols, max_sz, max_i, max_j;
    char empty, obs, full;
} t_bsq;

int process_map(FILE *f);

#endif
