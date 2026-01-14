/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:36:59 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:56:55 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function scans the first n bytes of the memory area pointed to by s
for the first occurrence of the character c.

Return Value:
This function returns a pointer to the matching byte or NULL
if the character is not found within the specified range. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (ptr[i] == (unsigned char)c)
		{
			return (&ptr[i]);
		}
		i++;
		n--;
	}
	return (NULL);
}
/* int main()
{
	const char str[] = "String test!";
	char *result = ft_memchr(str, 'i', 6);
	printf("The result is:%p\n", result);
	return (0);
} */
