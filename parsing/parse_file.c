/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:50 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 15:48:45 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	read_and_process_lines(int fd, t_cub *cub)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		if (!process_line(cub, line, &map_started))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

t_cub	*parse_cub_file(char *filename)
{
	t_cub	*cub;
	int		fd;

	if (!ends_with(filename, ".cub"))
		return (error_null("Error: File must have .cub extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_null("Error: Cannot open file"));
	cub = init_cub();
	if (!cub)
		return (NULL);
	if (!read_and_process_lines(fd, cub))
	{
		close(fd);
		free_cub(cub);
		return (NULL);
	}
	close(fd);
	if (!check_all_elements(cub) || !validate_map(&cub->map))
	{
		free_cub(cub);
		return (NULL);
	}
	return (cub);
}

static void	set_player_north_south(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.angle = -PI / 2;
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else
	{
		game->player.angle = PI / 2;
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

static void	set_player_east_west(t_game *game, char dir)
{
	if (dir == 'E')
	{
		game->player.angle = 0.0;
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.angle = PI;
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

void	init_player_from_map(t_game *game)
{
	t_map	*map;

	map = &game->cub->map;
	game->player.x = map->player_x * TILE + TILE / 2;
	game->player.y = map->player_y * TILE + TILE / 2;
	if (map->player_dir == 'N' || map->player_dir == 'S')
		set_player_north_south(game, map->player_dir);
	else if (map->player_dir == 'E' || map->player_dir == 'W')
		set_player_east_west(game, map->player_dir);
}
