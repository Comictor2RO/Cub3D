/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:56 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/26 16:42:50 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	add_map_line(t_map *map, char *line)
{
	char	**new_grid;
	int		i;
	int		len;

	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
		return (0);
	len = ft_strlen(new_grid[i]);
	if (len > 0 && new_grid[i][len - 1] == '\n')
		new_grid[i][len - 1] = '\0';
	new_grid[i + 1] = NULL;
	if (map->grid)
		free(map->grid);
	map->grid = new_grid;
	map->height++;
	if ((int)ft_strlen(new_grid[i]) > map->width)
		map->width = ft_strlen(new_grid[i]);
	return (1);
}

void	normalize_map(t_map *map)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len < map->width)
		{
			new_line = malloc(map->width + 1);
			if (!new_line)
				return ;
			j = 0;
			while (j < len)
			{
				new_line[j] = map->grid[i][j];
				j++;
			}
			while (j < map->width)
				new_line[j++] = ' ';
			new_line[j] = '\0';
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
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' ||
				map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error_msg("Error: Map must have exactly one spawn point"));
	return (1);
}
