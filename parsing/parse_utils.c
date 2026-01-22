/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:07:12 by vturlas           #+#    #+#             */
/*   Updated: 2026/01/22 17:07:14 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strtrim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
		start++;
	if (*start == 0)
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	starts_with(char *str, char *prefix)
{
	int	i;

	if (!str || !prefix)
		return (0);
	i = 0;
	while (prefix[i])
	{
		if (str[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

int	ends_with(char *str, char *suffix)
{
	int	str_len;
	int	suffix_len;
	int	i;

	if (!str || !suffix)
		return (0);
	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (0);
	i = 0;
	while (i < suffix_len)
	{
		if (str[str_len - suffix_len + i] != suffix[i])
			return (0);
		i++;
	}
	return (1);
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_content;

	if (!line)
		return (0);
	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && 
			line[i] != 'N' && line[i] != 'S' && 
			line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		if (line[i] == '0' || line[i] == '1' || 
			line[i] == 'N' || line[i] == 'S' || 
			line[i] == 'E' || line[i] == 'W')
			has_content = 1;
		i++;
	}
	return (has_content);
}
