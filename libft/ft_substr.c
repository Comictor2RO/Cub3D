/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:40:07 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:38:46 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function extracts a substring from the string s, starting at index start
and with a length of len characters.

Return Value:
This function returns a new string containing the extracted substring.
If the allocation fails, it returns NULL. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		dest[i] = s[start + i];
	return (dest);
}
/* int main()
{
    char *text = "Ana are mere";
    char *bucata;
    
    // Luăm textul "are" (începe de la poziția 4, lungime 3)
    bucata = ft_substr(text, 4, 3);
    printf("Am extras: %s\n", bucata);
    
    free(bucata);  // Eliberăm memoria
    return (0);
} */