/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:21:07 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:48:37 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
Thid function compares the first n characters of
the null-terminated strings s1 and s2.
It stops comparing when a null character (\0) is found
in either string or after n characters, whichever comes first.

Return Value:
The function returns an integer:
A value less than 0 if s1 is lexicographically less than s2.
0 if s1 and s2 are equal for the first n characters.
A value greater than 0 if s1 is lexicographically greater than s2. */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
/* int main()
{
	const char *str1 = "Test string";
	const char *str2 = "The second one";

	printf("This is the compare result: %d\n", ft_strncmp(str1, str2, 1));
	return (0);
} */