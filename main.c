/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:19 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/07 18:09:33 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	error_usage(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./cub3D <map.cub>\n");
		return (1);
	}
	if (!ends_with(argv[1], ".cub"))
	{
		printf("Error\nMap file must have .cub extension\n");
		return (1);
	}
	return (0);
}

static void	drawing(t_game *game)
{
	draw_3d_view(game);
	draw_map(game);
	draw_rays_on_minimap(game);
	draw_player_2d(game);
}

int	update_game(t_game *game)
{
	double	new_x;
	double	new_y;
	int		x;
	int		y;

	new_x = 0;
	new_y = 0;
	movements_up_down(game, new_x, new_y);
	movements_left_right(game, new_x, new_y);
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
	drawing(game);
	mlx_put_image_to_window(game->mlx, game->window, game->map_img.img, 0, 0);
	return (0);
}

static void	init_game_hooks(t_game game)
{
	init_player_from_map(&game);
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
	mlx_hook(game.window, 17, 1L << 17, close_game, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_loop(game.mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_cub	*cub;

	if (error_usage(argc, argv) == 1)
	{
		return (1);
	}
	cub = parse_cub_file(argv[1]);
	if (!cub)
		return (1);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	game.map_img.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.map_img.addr = mlx_get_data_addr(game.map_img.img, &game.map_img.bpp,
			&game.map_img.line_len, &game.map_img.endian);
	game.cub = cub;
	if (!load_all_textures(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	init_game_hooks(game);
	return (0);
}
