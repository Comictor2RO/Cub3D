#include "cub3d.h"

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