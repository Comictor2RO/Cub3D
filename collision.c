/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:57 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 16:51:37 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map_x < 0 || map_x >= game->cub->map.width
		|| map_y < 0 || map_y >= game->cub->map.height)
		return (1);
	if (game->cub->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}
