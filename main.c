#include "cub3d.h"

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
    if (moved)
    {
        draw_map(game->mlx, game->window);
        draw_circle(game->mlx, game->window, 
                    (int)game->player.x, (int)game->player.y, 4, 0x00FF0000);
        int line_len = 20;
        int end_x = (int)(game->player.x + cos(game->player.angle) * line_len);
        int end_y = (int)(game->player.y + sin(game->player.angle) * line_len);
        draw_line(game->mlx, game->window, 
                  (int)game->player.x, (int)game->player.y, end_x, end_y, 0x0000FF00);
    }
    usleep(16000);
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