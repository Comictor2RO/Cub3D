/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:08:29 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:46:25 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //de revenit si reanalizat codul
/* Description:
This function appends the string src to the string dst,ensuring that
the total length of the resulting string does not exceed the specified size size.
It always null-terminates the result unless size is 0 or the total length
is greater than or equal to size.

Return Value:
The function returns the total length of the string it tried to create,
i.e., the initial length of dst plus the length of src. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/* int main()
{
    char dst[20] = "Hello";
    const char *src = " World!";
    size_t dstsize = 15;
    size_t result;

    result = ft_strlcat(dst, src, dstsize);

    printf("Result: %zu\n", result);
    printf("Destination: '%s'\n\n", dst);
    return 0;
} */