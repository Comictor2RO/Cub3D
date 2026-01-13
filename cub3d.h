#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

typedef struct s_img {
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_player
{
    double x;
    double y;
    double angle;  // 0 = dreapta, PI/2 = sus etc.
} t_player;

typedef struct s_game
{
    void *mlx;
    void *window;
    t_player player;
    t_img map_img;
    int keys[4];
} t_game;