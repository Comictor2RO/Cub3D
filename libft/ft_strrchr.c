/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:03:43 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:36:28 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function locates the last occurrence of the character c in the string s.

Return Value:
This function returns a pointer to the last occurrence of c in s.
If c is not found, it returns NULL. */
char	*ft_strrchr(const char *s, int c)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	while (length >= 0)
	{
		if (s[length] == (char)c)
			return ((char *)(s + length));
		length--;
	}
	return (NULL);
}
/* int main()
{
	const char *str = "String 4 test 42 !";
	char *result = ft_strrchr(str, 's');
	printf("Last appearance of the input char is: %s\n", result);
	return (0);
} */