/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:38:25 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:51:32 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function removes leading and trailing whitespace characters
(or any characters specified in the set set) from the string s.

Return Value:
This function returns a new string
with the leading and trailing characters removed.
If memory allocation fails, it returns NULL. */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*str;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	str = malloc(sizeof(char) * (len - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], len - start + 1);
	return (str);
}
/* int main()
{
	const char *s1 = "---Hello 42---";
	const char *set = "-";
	printf("%s\n",ft_strtrim(s1, set));
	return 0;
} */