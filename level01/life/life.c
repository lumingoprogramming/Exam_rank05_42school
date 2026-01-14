#include "life.h"
char **alloc_board(int w, int h)
{
    char **b = malloc(sizeof(char*) * h);
    if(!b) return NULL;
    for(int i = 0; i < h; i++)
    {
        b[i] = malloc(w);
        if(!b[i]) return NULL;
        for(int j = 0; j < w; j++)
            b[i][j] = ' ';
    }
    return b;
}

void draw_initial(char **b, int w, int h)
{
    char c;
    int x = 0, y = 0, pen = 0;

    while( read(0, &c, 1) == 1)
    {
        if(c == 'w' && y > 0) y--;
        if(c == 's' && y < h-1) y++;
        if(c == 'a' && x > 0) x--;
        if(c == 'd' && x < w-1) x++;
        if(c == 'x') pen = !pen;
        if(pen)
            b[y][x] = 'O';
    }
}

static int neighbors(char **temp, int w, int h, int y, int x)
{
    int c = 0;
    for( int dy = -1; dy <= 1 ; dy++)
        for(int dx = -1; dx <= 1; dx++)
        {
            if(!dy && !dx)
                continue;
            int ny = y + dy, nx = x + dx;

            if(ny >= 0 && nx >= 0 && ny < h && nx < w)
            {
                if(temp[ny][nx] == 'O')
                    c++;
            }
        }
    return c;
}

void play(char **b, int w, int h)
{
    char **temp = alloc_board(w, h);

    for( int y = 0; y < h ; y++)
        for(int x = 0; x < w; x++)
        {
            int n = neighbors(b, w, h, y, x);

            if(b[y][x] == 'O') 
                temp[y][x] = (n == 2 || n == 3)? 'O' : ' ';
            else
                temp[y][x] = (n == 3)? 'O' : ' ';
        }

    for( int i = 0; i < h ; i++)
    {
        for(int j = 0; j < w; j++)
        {
            b[i][j] = temp[i][j];
        }
        free(temp[i]);
    }
    free(temp);
}

void print_board(char **b, int w, int h)
{
    for(int y = 0; y < h; y++)
    {
        write(1, b[y], w);
        write(1, "\n", 1);
    }
}

void free_board(char **b, int h)
{
    for(int y = 0; y < h; y++)
    {
        free(b[y]);
    }
    free(b);
}

int main(int argc, char **argv)
{
    if(argc != 4)
        return 1;

    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int iter = atoi(argv[3]);
    
    char **board = alloc_board(w,h);
    if(!board)
        return 1;
    draw_initial(board, w, h);

    while (iter--)
        play(board, w, h);

    print_board(board, w, h);
    free_board(board, h);
    return 0;
}