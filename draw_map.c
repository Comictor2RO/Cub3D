#include "cub3d.h"

static void draw_vertical_line(t_img *img, int x, int y, int len, int color)
{
    int i = 0;
    while(i < len)
    {
        my_mlx_pixel_put(img, x, y + i, color);
        i++;
    }
}

static void draw_horizontal_line(t_img *img, int x, int y, int len, int color)
{
    int i = 0;
    while(i < len)
    {
        my_mlx_pixel_put(img, x + i, y, color);
        i++;
    }
}

static void draw_tile(t_img *img, int x, int y, int color)
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