/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:43:49 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:46:43 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function searches for the first occurrence of the character c
in the string s.

Return Value:
This function returns a pointer to the first occurrence of c in s,
or NULL if c is not found. */
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
/* int main()
{
	const char *str = "Test string!";
	char *result = ft_strchr(str, 'e');
	printf("The result is: %s\n", result);
	return (0);
} */