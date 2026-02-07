/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:07:18 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/07 18:29:57 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid_pos(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (0);
	return (1);
}

static int	check_cell_surrounded(t_map *map, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (!is_valid_pos(map, nx, ny) || map->grid[ny][nx] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_map_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'N' ||
				map->grid[y][x] == 'S' || map->grid[y][x] == 'E' ||
				map->grid[y][x] == 'W')
			{
				if (!check_cell_surrounded(map, x, y))
					return (error_msg("Error: Map is not closed"));
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (map->height == 0)
		return (error_msg("Error: Empty map"));
	normalize_map(map);
	if (!find_player(map))
		return (0);
	if (!validate_map_closed(map))
		return (0);
	return (1);
}
