/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:43:45 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:47:47 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
strlcpy copies up to size - 1 characters from the string src to dst,
null-terminating the result.
It ensures that the destination string is always null-terminated,
even if the source string is longer than size - 1.

Return Value:
The function returns the total length of the string it tried to create,
i.e., the length of src. */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
/* int main() 
{
    char source[] = "Hello, world!";
    char destination[10];  // Smaller buffer

    size_t result = ft_strlcpy(destination, source, sizeof(destination));

    printf("Destination: %s\n", destination);  // Output: "Hello, wo"
    printf("Length of source: %zu\n", result);  // Output: 13

    return 0;
} */
