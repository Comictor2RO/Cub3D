/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vturlas <vturlas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:25:20 by ggabor            #+#    #+#             */
/*   Updated: 2025/10/10 15:48:45 by vturlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function creates a duplicate of the string s by allocating memory
and copying the content of s into it.

Return Value:
This function returns a pointer to the newly allocated string
that is a duplicate of s.
If memory allocation fails, it returns NULL. */
char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(src);
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (dest == 0)
		return (NULL);
	ft_memcpy(dest, src, len + 1);
	return (dest);
}
/* int main()
{
	const char *str = "Test string";
	char *dest;
	
	dest = ft_strdup(str);
	printf("Source string: %s\n", str);
	printf("Destination string:%s\n", dest);
	free(dest);
	return (0);
} */