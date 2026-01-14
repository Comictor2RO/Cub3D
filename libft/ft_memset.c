/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:41:42 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:01:05 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function sets the first n bytes of the memory area pointed to by s
to the value of the byte c.

Return Value:
This function returns a pointer to the memory area s. */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (ptr);
}
/* int main()
{
	char str[15] = "Test my string!";
	printf("String before change: %s\n", str);
	ft_memset(str, 'z', 4);
	printf("String after change: %s\n",str);

	return (0);	
} */