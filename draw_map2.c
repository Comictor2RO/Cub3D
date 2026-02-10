/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:11:28 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 16:11:42 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_tile(t_game *game, int x, int y, double s)
{
	int	i;
	int	j;

	i = (int)(x * TILE * s);
	while (i < (int)((x + 1) * TILE * s) && i < MINIMAP_WIDTH)
	{
		j = (int)(y * TILE * s);
		while (j < (int)((y + 1) * TILE * s) && j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&game->map_img, i, j, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}
