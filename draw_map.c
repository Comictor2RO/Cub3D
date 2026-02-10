/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:11 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 16:13:08 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_game *game, double scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)(game->cub->map.width * TILE * scale) && i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < (int)(game->cub->map.height * TILE * scale)
			&& j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&game->map_img, i, j, 0x00333333);
			j++;
		}
		i++;
	}
}

static double	get_minimap_scale(t_game *game)
{
	double	scale;

	scale = (double)MINIMAP_WIDTH / (game->cub->map.width * TILE);
	if ((game->cub->map.height * TILE * scale) > WINDOW_HEIGHT)
		scale = (double)WINDOW_HEIGHT / (game->cub->map.height * TILE);
	return (scale);
}

static void	draw_map_tiles(t_game *game, double s)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->cub->map.width)
	{
		y = 0;
		while (y < game->cub->map.height)
		{
			if (game->cub->map.grid[y][x] == '1')
				fill_tile(game, x, y, s);
			y++;
		}
		x++;
	}
}

static void	draw_map_grid(t_game *game, double scale)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	while (x <= game->cub->map.width)
	{
		j = 0;
		while (j < (int)(game->cub->map.height * TILE * scale)
			&& j < WINDOW_HEIGHT)
			my_mlx_pixel_put(&game->map_img,
				(int)(x * TILE * scale), j++, 0xFF000000);
		x++;
	}
	y = 0;
	while (y <= game->cub->map.height)
	{
		i = 0;
		while (i < (int)(game->cub->map.width * TILE * scale)
			&& i < MINIMAP_WIDTH)
			my_mlx_pixel_put(&game->map_img,
				i++, (int)(y * TILE * scale), 0xFF000000);
		y++;
	}
}

void	draw_map(t_game *game)
{
	double	scale;

	scale = get_minimap_scale(game);
	draw_background(game, scale);
	draw_map_tiles(game, scale);
	draw_map_grid(game, scale);
}
