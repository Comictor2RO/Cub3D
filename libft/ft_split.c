/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:24 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:44:19 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static int	free_array(char **array, int size)
{
	while (size--)
		free (array[size]);
	free (array);
	return (0);
}

static int	build_words(char **result, const char *s, char c)
{
	size_t	i;
	int		pos;
	size_t	len;
	size_t	start;

	i = 0;
	pos = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (i < len && s[i] == c)
			i++;
		if (i < len)
		{
			start = i;
			while (i < len && s[i] != c)
				i++;
			result[pos] = ft_substr(s, start, i - start);
			if (!result[pos])
				return (free_array(result, pos));
			pos++;
		}
	}
	result[pos] = NULL;
	return (1);
}

/* Description:
This function splits the string s into an array of strings
based on the delimiter c.
It returns an array where each element
is a substring from s, delimited by c.

Return Value:
This function returns a pointer to an array of strings.
NULL if the allocation fails. */
char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(words(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (build_words(result, s, c) == 0)
		return (NULL);
	return (result);
}
/* int main()
{
    char **result;
    const char *str = "This is a simple test";
    char delimiter = ' ';

    result = ft_split(str, delimiter);
    
    if (result)
    {
        int i = 0;
        while (result[i])
        {
            printf("Word %d: %s\n", i + 1, result[i]);
            free(result[i]);
            i++;
        }
        free(result);
    }
} */