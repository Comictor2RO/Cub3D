/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:06:24 by vturlas           #+#    #+#             */
/*   Updated: 2026/02/10 16:26:38 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_rgb_component(char *str, int *value)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != ' ' && str[i] != '\t')
				return (0);
			break ;
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num < 0 || num > 255)
		return (0);
	*value = num;
	return (1);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		return (error_msg("Error: Invalid RGB format (need R,G,B)"));
	}
	if (!parse_rgb_component(split[0], &r)
		|| !parse_rgb_component(split[1], &g)
		|| !parse_rgb_component(split[2], &b))
	{
		free_split(split);
		return (error_msg("Error: RGB values must be 0-255"));
	}
	color->r = r;
	color->g = g;
	color->b = b;
	color->hex = rgb_to_hex(r, g, b);
	free_split(split);
	return (1);
}

static int	controls(t_cub *cub, char *trimmed, char *rgb_str, int result)
{
	if (starts_with(trimmed, "F "))
	{
		if (cub->floor.r != -1)
			return (error_msg("Error: Duplicate floor color"));
		rgb_str = trimmed + 2;
		while (*rgb_str == ' ' || *rgb_str == '\t')
			rgb_str++;
		result = parse_rgb(rgb_str, &cub->floor);
	}
	else if (starts_with(trimmed, "C "))
	{
		if (cub->ceiling.r != -1)
			return (error_msg("Error: Duplicate ceiling color"));
		rgb_str = trimmed + 2;
		while (*rgb_str == ' ' || *rgb_str == '\t')
			rgb_str++;
		result = parse_rgb(rgb_str, &cub->ceiling);
	}
	return (result);
}

int	parse_color_line(t_cub *cub, char *line)
{
	char	*trimmed;
	char	*rgb_str;
	int		result;

	trimmed = ft_strtrim_whitespace(line);
	rgb_str = NULL;
	result = 0;
	result = controls(cub, trimmed, rgb_str, result);
	free(trimmed);
	return (result);
}
