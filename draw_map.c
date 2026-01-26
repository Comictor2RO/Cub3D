/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:11 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/26 17:11:32 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_game *game)
{
	int		x;
	int		y;
	double	scale;
	int		scaled_x;
	int		scaled_y;
	int		scaled_x2;
	int		scaled_y2;
	int		i;
	int		j;

	// Calculăm factorul de scalare pentru a încăpea toată harta în minimap
	scale = (double)MINIMAP_WIDTH / (game->cub->map.width * TILE);
	if ((game->cub->map.height * TILE * scale) > WINDOW_HEIGHT)
		scale = (double)WINDOW_HEIGHT / (game->cub->map.height * TILE);
	
	// Desenăm fundalul minimap-ului
	i = 0;
	while (i < (int)(game->cub->map.width * TILE * scale) && i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < (int)(game->cub->map.height * TILE * scale) && j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&game->map_img, i, j, 0x00333333);
			j++;
		}
		i++;
	}
	
	// Desenăm tile-urile
	x = 0;
	while (x < game->cub->map.width)
	{
		y = 0;
		while (y < game->cub->map.height)
		{
			// Calculăm coordonatele scalate pentru colțurile tile-ului
			scaled_x = (int)(x * TILE * scale);
			scaled_y = (int)(y * TILE * scale);
			scaled_x2 = (int)((x + 1) * TILE * scale);
			scaled_y2 = (int)((y + 1) * TILE * scale);
			
			if (scaled_x < MINIMAP_WIDTH && scaled_y < WINDOW_HEIGHT)
			{
				if (game->cub->map.grid[y][x] == '1')
				{
					i = scaled_x;
					while (i < scaled_x2 && i < MINIMAP_WIDTH)
					{
						j = scaled_y;
						while (j < scaled_y2 && j < WINDOW_HEIGHT)
						{
							my_mlx_pixel_put(&game->map_img, i, j, 0x00FFFFFF);
							j++;
						}
						i++;
					}
				}
			}
			y++;
		}
		x++;
	}
	
	// Desenăm grid-ul
	x = 0;
	while (x <= game->cub->map.width)
	{
		scaled_x = (int)(x * TILE * scale);
		if (scaled_x < MINIMAP_WIDTH)
		{
			j = 0;
			while (j < (int)(game->cub->map.height * TILE * scale) && j < WINDOW_HEIGHT)
			{
				my_mlx_pixel_put(&game->map_img, scaled_x, j, 0xFF000000);
				j++;
			}
		}
		x++;
	}
	y = 0;
	while (y <= game->cub->map.height)
	{
		scaled_y = (int)(y * TILE * scale);
		if (scaled_y < WINDOW_HEIGHT)
		{
			i = 0;
			while (i < (int)(game->cub->map.width * TILE * scale) && i < MINIMAP_WIDTH)
			{
				my_mlx_pixel_put(&game->map_img, i, scaled_y, 0xFF000000);
				i++;
			}
		}
		y++;
	}
}
