/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:20:09 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:54:55 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function sets the first n bytes of the memory area pointed to by s to zero,
effectively clearing the memory.

Return Value:
This function does not return a value. */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/* int main()
{
	char str[15] = "Test my string!";
	printf("String before change: %s\n", str);
	ft_bzero(str, 4);
	printf("String after change: %s\n",str);

	return (0);	
} */