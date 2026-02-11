/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:13 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:16 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_img *img, t_circle p)
{
	int	y;

	y = p.cy - p.r;
	while (y <= p.cy + p.r)
	{
		draw_circle_line(img, p, y);
		y++;
	}
}

void	draw_line(t_img *img, t_line p)
{
	t_bresenham	b;

	init_bresenham(&b, p);
	while (1)
	{
		my_mlx_pixel_put(img, p.x1, p.y1, p.color);
		if (p.x1 == p.x2 && p.y1 == p.y2)
			break ;
		update_line_pos(&p, &b);
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
	if (player_x >= 0 && player_x < MINIMAP_WIDTH
		&& player_y >= 0 && player_y < WINDOW_HEIGHT)
	{
		draw_circle(&game->map_img, (t_circle){player_x, player_y,
			4, 0x00FF0000});
		end_x = (int)(player_x + cos(game->player.angle) * 15);
		end_y = (int)(player_y + sin(game->player.angle) * 15);
		draw_line(&game->map_img, (t_line){player_x, player_y, end_x,
			end_y, 0x00FFFF00});
	}
}
