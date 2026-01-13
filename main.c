#include "cub3d.h"
#include <stdlib.h>

#define Map_Width       10
#define Map_Height      10
#define Tile            32
#define Window_Width    1024
#define Window_Height   512
#define MOVE_SPEED      1.33
#define ROT_SPEED       0.075

int map[Map_Width][Map_Height] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }
};

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dest;

    dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dest = color;
}

void draw_vertical_line(t_img *img, int x, int y, int len, int color)
{
    int i = 0;
    while(i < len)
    {
        my_mlx_pixel_put(img, x, y + i, color);
        i++;
    }
}

void draw_horizontal_line(t_img *img, int x, int y, int len, int color)
{
    int i = 0;
    while(i < len)
    {
        my_mlx_pixel_put(img, x + i, y, color);
        i++;
    }
}

void draw_tile(t_img *img, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while(i < Tile)
    {
        j = 0;
        while(j < Tile)
        {
            my_mlx_pixel_put(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_map(void *mlx, void *window)
{
    int x;
    int y;
    t_img img;

    img.img = mlx_new_image(mlx, Map_Width * Tile, Map_Height * Tile);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

    x = 0;
    while(x < Map_Width)
    {
        y = 0;
        while(y < Map_Height)
        {
            if(map[y][x] == 1)
                draw_tile(&img, x * Tile, y * Tile, 0x00FFFFFF);
            else
                draw_tile(&img, x * Tile, y * Tile, 0x00333333);
            y++;
        }
        x++;
    }

    x = 0;
    while (x < Map_Width)
    {
        y = 0;
        while (y < Map_Height)
        {
            draw_vertical_line(&img, (x + 1) * Tile - 1, y * Tile, Tile, 0xFF000000);
            draw_horizontal_line(&img, x * Tile, (y + 1) * Tile - 1, Tile, 0xFF000000);
            y++;
        }
        x++;
    }

    mlx_put_image_to_window(mlx, window, img.img, 0, 0);
}

int check_collision(double x, double y)
{
    int map_x = (int)(x / Tile);
    int map_y = (int)(y / Tile);
    
    if (map_x < 0 || map_x >= Map_Width || map_y < 0 || map_y >= Map_Height)
        return (1);  // în afara hărții
    if (map[map_y][map_x] == 1)
        return (1);  // perete
    return (0);  // liber
}

void draw_circle(void *mlx, void *window, int cx, int cy, int r, int color)
{
    int x;
    int y;
    int dx;
    int dy;

    y = cy - r;
    while(y <= cy + r)
    {
        x = cx - r;
        while(x <= cx + r)
        {

            dx = x - cx;
            dy = y - cy;
            if(dx * dx + dy * dy <= r * r)
                mlx_pixel_put(mlx, window, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_line(void *mlx, void *window, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx, window, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

int handle_key(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
    {
        mlx_destroy_window(game->mlx, game->window);
        exit(0);
    }
    
    if (keycode == 119 || keycode == 'w')
        game->keys[0] = 1;  // W
    if (keycode == 115 || keycode == 's')
        game->keys[1] = 1;  // S
    if (keycode == 97  || keycode == 'a')
        game->keys[2] = 1;  // A
    if (keycode == 100 || keycode == 'd')
        game->keys[3] = 1;  // D
    return (0);
}

int handle_key_release(int keycode, t_game *game)
{
    if (keycode == 119 || keycode == 'w')
        game->keys[0] = 0;
    if (keycode == 115 || keycode == 's')
        game->keys[1] = 0;
    if (keycode == 97  || keycode == 'a')
        game->keys[2] = 0;
    if (keycode == 100 || keycode == 'd')
        game->keys[3] = 0;
    return (0);
}

int update_game(t_game *game)
{
    double new_x, new_y;
    int moved = 0;
    
    if (game->keys[0])  // W - inainte
    {
        new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
        new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
        if (!check_collision(new_x, new_y))
        {
            game->player.x = new_x;
            game->player.y = new_y;
            moved = 1;
        }
    }
    if (game->keys[1])  // S - inapoi
    {
        new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
        new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
        if (!check_collision(new_x, new_y))
        {
            game->player.x = new_x;
            game->player.y = new_y;
            moved = 1;
        }
    }
    if (game->keys[2])  // A - rotire stanga
    {
        game->player.angle -= ROT_SPEED;
        moved = 1;
    }
    if (game->keys[3])  // D - rotire dreapta
    {
        game->player.angle += ROT_SPEED;
        moved = 1;
    }

    // Redesenare DOAR daca s-a miscat ceva
    if (moved)
    {
        draw_map(game->mlx, game->window);
        draw_circle(game->mlx, game->window, 
                    (int)game->player.x, (int)game->player.y, 4, 0x00FF0000);
        
        // Desenare linie directie
        int line_len = 20;
        int end_x = (int)(game->player.x + cos(game->player.angle) * line_len);
        int end_y = (int)(game->player.y + sin(game->player.angle) * line_len);
        draw_line(game->mlx, game->window, 
                  (int)game->player.x, (int)game->player.y, end_x, end_y, 0x0000FF00);
    }
    
    usleep(16000);  // ~60 FPS limiter
    return (0);
}

int main(void)
{
    t_game game;
    
    game.mlx = mlx_init();
    game.window = mlx_new_window(game.mlx, Window_Width, Window_Height, "Cub3D");
    
    // Pozitie initiala player in mijlocul hartii
    game.player.x = 5 * Tile + Tile / 2;  // tile 5,5
    game.player.y = 5 * Tile + Tile / 2;
    game.player.angle = 0.0;  // priveste spre dreapta
    
    // Initializare keys la 0
    game.keys[0] = game.keys[1] = game.keys[2] = game.keys[3] = 0;

    // Prima desenare
    draw_map(game.mlx, game.window);
    draw_circle(game.mlx, game.window, 
                (int)game.player.x, (int)game.player.y, 4, 0x00FF0000);

    // HOOK-URI
    mlx_hook(game.window, 2, 1L<<0, handle_key, &game);          // KeyPress
    mlx_hook(game.window, 3, 1L<<1, handle_key_release, &game);  // KeyRelease
    mlx_loop_hook(game.mlx, update_game, &game);                 // Update continuu
    mlx_loop(game.mlx);
    return (0);
}