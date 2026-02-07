/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:13 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/07 17:58:25 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_img *img, int cx, int cy, int r, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = cy - r;
	while (y <= cy + r)
	{
		x = cx - r;
		while (x <= cx + r)
		{
			dx = x - cx;
			dy = y - cy;
			if (dx * dx + dy * dy <= r * r)
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
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

void	draw_player_2d(t_game *game)
{
	int		end_x;
	int		end_y;
	double	scale;
	int		player_x;
	int		player_y;

	scale = (double)MINIMAP_WIDTH / (game->cub->map.width * TILE);
	if ((game->cub->map.height * TILE * scale) > WINDOW_HEIGHT)
		scale = (double)WINDOW_HEIGHT / (game->cub->map.height * TILE);
	player_x = (int)(game->player.x * scale);
	player_y = (int)(game->player.y * scale);
	if (player_x >= 0 && player_x < MINIMAP_WIDTH && 
		player_y >= 0 && player_y < WINDOW_HEIGHT)
	{
		draw_circle(&game->map_img, player_x, player_y, 4, 0x00FF0000);
		end_x = (int)(player_x + cos(game->player.angle) * 15);
		end_y = (int)(player_y + sin(game->player.angle) * 15);
		draw_line(&game->map_img, player_x, player_y, end_x, end_y, 0x00FFFF00);
	}
}
