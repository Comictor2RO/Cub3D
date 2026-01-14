/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:08:48 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:45:13 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function locates the first occurrence of the substring needle
within the string haystack,searching up to len characters.
It returns a pointer to the beginning of the found substring,
or NULL if the substring is not found.
Return Value:
This function returns a pointer to the first occurrence of needle in haystack
within the first len characters. If needle is not found, it returns NULL. */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
/* int main()
{
    const char *haystack = "Test string!";
    const char *needle = "string";
    char *result = ft_strnstr(haystack, needle, 12);

    printf("Found '%s' at pointer address: %p\n", result, result);

    return 0;
} */