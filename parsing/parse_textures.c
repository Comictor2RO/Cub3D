/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:07:04 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 15:49:11 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	validate_texture_path(char *trimmed)
{
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (error_msg("Error: Invalid texture path"));
	}
	if (!ends_with(trimmed, ".xpm"))
	{
		free(trimmed);
		return (error_msg("Error: Texture must be .xpm file"));
	}
	if (access(trimmed, F_OK) == -1)
	{
		free(trimmed);
		return (error_msg("Error: Texture file not found"));
	}
	return (1);
}

static int	parse_texture_line(char *line, char *id, t_texture *tex)
{
	char	*path;
	char	*trimmed;

	if (!starts_with(line, id))
		return (0);
	if (tex->path != NULL)
		return (error_msg("Error: Duplicate texture identifier"));
	path = line + ft_strlen(id);
	while (*path == ' ' || *path == '\t')
		path++;
	trimmed = ft_strtrim_whitespace(path);
	if (!validate_texture_path(trimmed))
		return (0);
	tex->path = trimmed;
	return (1);
}

int	parse_textures(t_cub *cub, char *line)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim_whitespace(line);
	result = 0;
	if (starts_with(trimmed, "NO "))
		result = parse_texture_line(trimmed, "NO ", &cub->tex_north);
	else if (starts_with(trimmed, "SO "))
		result = parse_texture_line(trimmed, "SO ", &cub->tex_south);
	else if (starts_with(trimmed, "WE "))
		result = parse_texture_line(trimmed, "WE ", &cub->tex_west);
	else if (starts_with(trimmed, "EA "))
		result = parse_texture_line(trimmed, "EA ", &cub->tex_east);
	free(trimmed);
	return (result);
}

static int	load_texture(t_game *game, t_texture *tex)
{
	if (!tex->path)
		return (error_msg("Error: Texture path is NULL"));
	tex->img = mlx_xpm_file_to_image(game->mlx, tex->path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (error_msg("Error: Failed to load texture"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (error_msg("Error: Failed to get texture data"));
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->cub->tex_north))
		return (0);
	if (!load_texture(game, &game->cub->tex_south))
		return (0);
	if (!load_texture(game, &game->cub->tex_west))
		return (0);
	if (!load_texture(game, &game->cub->tex_east))
		return (0);
	return (1);
}
