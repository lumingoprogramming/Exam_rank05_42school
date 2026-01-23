#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsq.h"

static int min3(int a, int b, int c) {
    return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

static void free_grid(char **grid, int rows) {
    if (!grid) return;
    for (int i = 0; i < rows; i++)
        free(grid[i]);
    free(grid);
}

static int parse_header(FILE *f, t_bsq *bsq) {
    if (fscanf(f, "%d %c %c %c\n", &bsq->rows, &bsq->empty, &bsq->obs, &bsq->full) != 4)
        return -1;
    if (bsq->rows <= 0 || bsq->empty == bsq->obs || bsq->empty == bsq->full || 
        bsq->obs == bsq->full || bsq->empty < 32 || bsq->obs < 32 || bsq->full < 32)
        return -1;
    return 0;
}

static int load_map(FILE *f, t_bsq *bsq) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    bsq->grid = malloc((bsq->rows + 1) * sizeof(char *));
    if (!bsq->grid) return -1;
    bsq->grid[bsq->rows] = NULL;
    
    for (int i = 0; i < bsq->rows; i++) {
        if ((read = getline(&line, &len, f)) == -1) {
            free(line);
            free_grid(bsq->grid, i);
            return -1;
        }
        if (line[read - 1] == '\n') read--;
        else {
            free(line);
            free_grid(bsq->grid, i);
            return -1;
        }
        
        bsq->grid[i] = strndup(line, read);
        if (!bsq->grid[i]) {
            free(line);
            free_grid(bsq->grid, i);
            return -1;
        }
        
        if (i == 0) bsq->cols = read;
        else if (bsq->cols != read) {
            free(line);
            free_grid(bsq->grid, i + 1);
            return -1;
        }
        
        for (int j = 0; j < read; j++) {
            if (line[j] != bsq->empty && line[j] != bsq->obs) {
                free(line);
                free_grid(bsq->grid, i + 1);
                return -1;
            }
        }
    }
    free(line);
    return 0;
}

static void find_square(t_bsq *bsq) {
    bsq->dp = calloc(bsq->rows * bsq->cols, sizeof(int));
    if (!bsq->dp) return;
    
    bsq->max_sz = 0;
    for (int i = 0; i < bsq->rows; i++) {
        for (int j = 0; j < bsq->cols; j++) {
            int idx = i * bsq->cols + j;
            if (bsq->grid[i][j] == bsq->obs)
                bsq->dp[idx] = 0;
            else if (i == 0 || j == 0)
                bsq->dp[idx] = 1;
            else {
                int up = bsq->dp[(i-1) * bsq->cols + j];
                int diag = bsq->dp[(i-1) * bsq->cols + (j-1)];
                int left = bsq->dp[i * bsq->cols + (j-1)];
                bsq->dp[idx] = min3(up, diag, left) + 1;
            }
            
            if (bsq->dp[idx] > bsq->max_sz) {
                bsq->max_sz = bsq->dp[idx];
                bsq->max_i = i - bsq->dp[idx] + 1;
                bsq->max_j = j - bsq->dp[idx] + 1;
            }
        }
    }
    free(bsq->dp);
}

static void print_result(t_bsq *bsq) {
    for (int i = bsq->max_i; i < bsq->max_i + bsq->max_sz; i++)
        for (int j = bsq->max_j; j < bsq->max_j + bsq->max_sz; j++)
            if (i < bsq->rows && j < bsq->cols)
                bsq->grid[i][j] = bsq->full;
    
    for (int i = 0; i < bsq->rows; i++)
        fprintf(stdout, "%s\n", bsq->grid[i]);
}

int process_map(FILE *f) {
    t_bsq bsq = {0};
    
    if (parse_header(f, &bsq) == -1)
        return -1;
    if (load_map(f, &bsq) == -1)
        return -1;
    
    find_square(&bsq);
    print_result(&bsq);
    free_grid(bsq.grid, bsq.rows);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        if (process_map(stdin) == -1)
            fprintf(stderr, "map error\n");
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (!f || process_map(f) == -1)
                fprintf(stderr, "map error\n");
            if (f) fclose(f);
            if (i < argc - 1)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}
