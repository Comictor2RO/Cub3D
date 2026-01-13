#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

#define Map_Width       10
#define Map_Height      10
#define Tile            32
#define Window_Width    1024
#define Window_Height   512
#define MOVE_SPEED      1.33
#define ROT_SPEED       0.075

extern int map[Map_Width][Map_Height];

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
    double angle;  //in radiani adica 0 = drept, PI/2 = sus, Pi = stanga, 3*PI/4 = jos, 2*PI = 0.
} t_player;

typedef struct s_game
{
    void *mlx;
    void *window;
    t_player player;
    t_img map_img;
    int keys[4];
} t_game;

void draw_map(void *mlx, void *window);         //draw_map.c
int check_collision(double x, double y);        //collision.c
void draw_circle(void *mlx, void *window, int cx, int cy, int r, int color);            //draw_player.c
void draw_line(void *mlx, void *window, int x1, int y1, int x2, int y2, int color);     //draw_player.c
int handle_key(int keycode, t_game *game);              //handle_hooks.c
int handle_key_release(int keycode, t_game *game);      //handle_hooks.c
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);      //utils.c