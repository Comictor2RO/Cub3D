#include "cub3d.h"

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