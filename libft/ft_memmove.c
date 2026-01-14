/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:08:23 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:50:51 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function copies n bytes from the memory area pointed to by src
to the memory area pointed to by dest,
handling overlapping memory areas correctly.

Return Value:
This function returns a pointer to dest. */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;

	ptr_dest = dest;
	if (ptr_dest < (unsigned char *) src)
		return (ft_memcpy(dest, src, n));
	else if (ptr_dest > (unsigned char *) src)
	{
		while (n--)
			ptr_dest[n] = ((unsigned char *) src)[n];
	}
	return (dest);
}
/* int main()
{
    char buffer[20] = "Overlap example";

    ft_memmove(buffer + 8, buffer, 7);
    printf("Result: %s\n", buffer);
    return 0;
} */