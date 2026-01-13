#include "cub3d.h"

int check_collision(double x, double y)
{
    int map_x = (int)(x / Tile);
    int map_y = (int)(y / Tile);
    
    if (map_x < 0 || map_x >= Map_Width || map_y < 0 || map_y >= Map_Height)
        return (1);
    if (map[map_y][map_x] == 1)
        return (1);
    return (0);
}