/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:40:55 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/11 15:45:35 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_cub	*init_cub(void)
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

int	check_all_elements(t_cub *cub)
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

static char	*append_buffer(char *line, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(line, buffer);
	free(line);
	return (temp);
}

char	*read_line(int fd)
{
	char	*line;
	char	buffer[2];
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
			return (append_buffer(line, buffer));
		line = append_buffer(line, buffer);
	}
	if (ret < 0 || (ret == 0 && ft_strlen(line) == 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	process_line(t_cub *cub, char *line, int *map_started)
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
