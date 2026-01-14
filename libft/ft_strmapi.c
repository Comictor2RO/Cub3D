/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:31:09 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:49:01 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // de facut main de test
/* Description:
Applies the function f to each character of the string s,
passing the index of the character as the first argument
and the character itself as the second.
It creates a new string (using malloc) to collect the results
from the successive applications of f.

Return Value:
The function returns the new string created from 
the successive applications of f.
If the memory allocation fails, it returns NULL. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
