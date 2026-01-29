#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char **alloc_board(int w, int h)
{
    char **b = malloc(sizeof(char *) * h);     // allocate row pointers
    if (!b) 
        return NULL;

    for (int i = 0; i < h; i++)
    {
        b[i] = malloc(sizeof(char) * w);       // allocate each row
        if (!b[i])
            return NULL;
        for (int j = 0; j < w; j++)
            b[i][j] = ' ';                     // initialize cell as dead
    }
    return b;
}

void draw_initial(char **b, int w, int h)
{
    char c;
    int x = 0, y = 0;                           // pen position
    int pen = 0;                                // pen off initially

    while (read(0, &c, 1) == 1)
    {
        if (c == 'w' && y > 0)
            y--;                                 // move up
        if (c == 's' && y < h - 1)
            y++;                                 // move down
        if (c == 'a' && x > 0)
            x--;                                 // move left
        if (c == 'd' && x < w - 1)
            x++;                                 // move right
        if (c == 'x')
            pen = !pen;                           // toggle pen
        if (pen)
            b[y][x] = 'O';                        // draw alive cell
    }
}

static int neighbors(char **b, int w, int h, int y, int x)
{
    int c = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (!dy && !dx)
                continue;                        // skip the cell itself
            int ny = y + dy, nx = x + dx;

            if (ny >= 0 && nx >= 0 && ny < h && nx < w)
            {
                if (b[ny][nx] == 'O')
                    c++;                           // count alive neighbors
            }
        }
    }
    return c;
}

void play(char **b, int w, int h)
{
    char **tmp = alloc_board(w, h);             // temporary grid

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) 
        {
            int n = neighbors(b, w, h, y, x);   // count 8 neighbors

            if (b[y][x] == 'O')                 // already alive cell
                tmp[y][x] = (n == 2 || n == 3) ? 'O' : ' ';
            else                                // already dead cell
                tmp[y][x] = (n == 3) ? 'O' : ' ';
        }

    // copy new generation back into main board
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            b[i][j] = tmp[i][j];                // overwrite original
        free(tmp[i]);
    }                           // free tmp row
    free(tmp);                                   // free tmp pointer list
}

void print_board(char **b, int w, int h)
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
            putchar(b[y][x]);   // print each cell
        putchar('\n');           // newline
    }
}


void free_board(char **b, int h)
{
    for (int i = 0; i < h; i++)
        free(b[i]);                             // free row
    free(b);                                    // free pointer list
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    int w = atoi(argv[1]);                      // width
    int h = atoi(argv[2]);                      // height
    int iter = atoi(argv[3]);                   // iterations

    char **board = alloc_board(w, h);
    if (!board) 
        return 1;

    draw_initial(board, w, h);                  // build initial pattern

    while (iter--)                               // run Game of Life
        play(board, w, h);

    print_board(board, w, h);                   // output result
    free_board(board, h);                       // free memory
    return 0;
}
