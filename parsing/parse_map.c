/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:56 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 17:09:46 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	add_map_line(t_map *map, char *line)
{
	char	**new_grid;

	new_grid = allocate_new_grid(map);
	if (!new_grid)
		return (0);
	if (!process_new_line(new_grid, map->height, line))
		return (0);
	if (map->grid)
		free(map->grid);
	map->grid = new_grid;
	if ((int)ft_strlen(new_grid[map->height]) > map->width)
		map->width = ft_strlen(new_grid[map->height]);
	map->height++;
	return (1);
}

void	normalize_map(t_map *map)
{
	int		i;
	int		len;
	char	*new_line;

	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len < map->width)
		{
			new_line = create_padded_line(map->grid[i], map->width);
			if (!new_line)
				return ;
			free(map->grid[i]);
			map->grid[i] = new_line;
		}
		i++;
	}
}

int	find_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			save_player(map, x, y, &count);
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error_msg("Error: Map must have exactly one spawn point"));
	return (1);
}
