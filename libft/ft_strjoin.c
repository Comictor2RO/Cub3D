/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:20:33 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:48:11 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
Allocates and returns a new string,
which is the result of concatenating the string s1 (the prefix)
with s2 (the suffix).
The function uses malloc to allocate memory for the new string.

Return Value:
The function returns a pointer to the new string,
or NULL if the memory allocation fails. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
/* int	main()
{
	char *str1 = "Hello ";
	char *str2 = "World!";
	char *result = ft_strjoin(str1, str2);
	printf("%s\n", result);
	return 0;
} */