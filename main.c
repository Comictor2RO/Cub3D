/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:19 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/15 16:48:31 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_game(t_game *game)
{
	double	new_x;
	double	new_y;
	int		x;
	int		y;

	if (game->keys[0])
	{
		new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
		if (!check_collision(new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys[1])
	{
		new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
		if (!check_collision(new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys[2])
	{
		new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
		if (!check_collision(new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->keys[3])
	{
		new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
		new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
		if (!check_collision(new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(&game->map_img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	draw_map(game);
	draw_3d_view(game);
	draw_player_2d(game);
	mlx_put_image_to_window(game->mlx, game->window, game->map_img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	game.map_img.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.map_img.addr = mlx_get_data_addr(game.map_img.img, &game.map_img.bpp,
			&game.map_img.line_len, &game.map_img.endian);
	game.player.x = 5 * TILE + TILE / 2;
	game.player.y = 5 * TILE + TILE / 2;
	game.player.angle = 0.0;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.player.plane_x = 0.0;
	game.player.plane_y = 0.66;
	game.keys[0] = 0;
	game.keys[1] = 0;
	game.keys[2] = 0;
	game.keys[3] = 0;
	game.mouse_x = WINDOW_WIDTH / 2;
	game.mouse_y = WINDOW_HEIGHT / 2;
	mlx_mouse_hide(game.mlx, game.window);
	mlx_mouse_move(game.mlx, game.window, game.mouse_x, game.mouse_y);
	mlx_hook(game.window, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.window, 3, 1L << 1, handle_key_release, &game);
	mlx_hook(game.window, 6, 1L << 6, handle_mouse_move, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
