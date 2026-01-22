/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:42 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 17:06:44 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	error_msg(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	return (0);
}

void	*error_null(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	if (cub->tex_north.path)
		free(cub->tex_north.path);
	if (cub->tex_south.path)
		free(cub->tex_south.path);
	if (cub->tex_west.path)
		free(cub->tex_west.path);
	if (cub->tex_east.path)
		free(cub->tex_east.path);
	if (cub->map.grid)
	{
		i = 0;
		while (i < cub->map.height)
		{
			free(cub->map.grid[i]);
			i++;
		}
		free(cub->map.grid);
	}
	free(cub);
}
