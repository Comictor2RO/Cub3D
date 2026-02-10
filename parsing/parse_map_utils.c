/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:56:13 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 17:12:33 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**allocate_new_grid(t_map *map)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	return (new_grid);
}

int	process_new_line(char **new_grid, int i, char *line)
{
	int	len;

	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
		return (0);
	len = ft_strlen(new_grid[i]);
	if (len > 0 && new_grid[i][len - 1] == '\n')
		new_grid[i][len - 1] = '\0';
	new_grid[i + 1] = NULL;
	return (1);
}

char	*create_padded_line(char *old_line, int width)
{
	char	*new_line;
	int		j;
	int		len;

	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	len = ft_strlen(old_line);
	j = 0;
	while (j < len)
	{
		new_line[j] = old_line[j];
		j++;
	}
	while (j < width)
		new_line[j++] = ' ';
	new_line[j] = '\0';
	return (new_line);
}

void	save_player(t_map *map, int x, int y, int *count)
{
	if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' ||
		map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
	{
		map->player_x = x;
		map->player_y = y;
		map->player_dir = map->grid[y][x];
		(*count)++;
	}
}
