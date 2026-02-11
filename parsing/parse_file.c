/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:50 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 15:43:30 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_cub	*parse_cub_file(char *filename)
{
	t_cub	*cub;
	char	*line;
	int		fd;
	int		map_started;

	if (!ends_with(filename, ".cub"))
		return (error_null("Error: File must have .cub extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_null("Error: Cannot open file"));
	cub = init_cub();
	if (!cub)
		return (NULL);
	map_started = 0;
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		if (!process_line(cub, line, &map_started))
		{
			free(line);
			close(fd);
			free_cub(cub);
			return (NULL);
		}
		free(line);
	}
	close(fd);
	if (!check_all_elements(cub) || !validate_map(&cub->map))
	{
		free_cub(cub);
		return (NULL);
	}
	return (cub);
}

void	init_player_from_map(t_game *game)
{
	t_map	*map;

	map = &game->cub->map;
	game->player.x = map->player_x * TILE + TILE / 2;
	game->player.y = map->player_y * TILE + TILE / 2;
	if (map->player_dir == 'N')
	{
		game->player.angle = -PI / 2;
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (map->player_dir == 'S')
	{
		game->player.angle = PI / 2;
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (map->player_dir == 'E')
	{
		game->player.angle = 0.0;
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (map->player_dir == 'W')
	{
		game->player.angle = PI;
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}
