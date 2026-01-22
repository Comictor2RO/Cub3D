/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:50 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 17:15:27 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	ft_memset(cub, 0, sizeof(t_cub));
	cub->floor.r = -1;
	cub->floor.g = -1;
	cub->floor.b = -1;
	cub->ceiling.r = -1;
	cub->ceiling.g = -1;
	cub->ceiling.b = -1;
	return (cub);
}

static int	check_all_elements(t_cub *cub)
{
	if (!cub->tex_north.path)
		return (error_msg("Error: Missing NO texture"));
	if (!cub->tex_south.path)
		return (error_msg("Error: Missing SO texture"));
	if (!cub->tex_west.path)
		return (error_msg("Error: Missing WE texture"));
	if (!cub->tex_east.path)
		return (error_msg("Error: Missing EA texture"));
	if (cub->floor.r == -1)
		return (error_msg("Error: Missing F color"));
	if (cub->ceiling.r == -1)
		return (error_msg("Error: Missing C color"));
	if (cub->map.height == 0)
		return (error_msg("Error: Missing map"));
	return (1);
}

static char	*read_line(int fd)
{
	char	*line;
	char	buffer[2];
	char	*temp;
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		ret = read(fd, buffer, 1);
		if (ret <= 0)
			break ;
		buffer[1] = '\0';
		if (buffer[0] == '\n')
		{
			temp = ft_strjoin(line, buffer);
			free(line);
			return (temp);
		}
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
	}
	if (ret < 0 || (ret == 0 && ft_strlen(line) == 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	process_line(t_cub *cub, char *line, int *map_started)
{
	if (is_empty_line(line))
		return (1);
	if (*map_started)
		return (add_map_line(&cub->map, line));
	if (is_map_line(line))
	{
		*map_started = 1;
		return (add_map_line(&cub->map, line));
	}
	if (parse_textures(cub, line) || parse_color_line(cub, line))
		return (1);
	return (error_msg("Error: Invalid line in file"));
}

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
