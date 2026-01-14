/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:28:02 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:44:52 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function copies n bytes from the memory area pointed to by src
to the memory area pointed to by dest.
The memory areas must not overlap.

Return Value:
This function returns a pointer to dest. */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/* int	main()
{
	char src[] = "Mem copy test!";
	char dest[20];
	
	ft_memcpy(dest, src, 8);
	printf("Copied string to destination: %s\n", dest);
	return (0);
} */