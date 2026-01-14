/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:30:32 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:28:52 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function calculates the length of s.

Return Value:
This function returns the number of characters in s,
excluding the terminating NUL byte (i.e., '\0'). */
size_t	ft_strlen(const char*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
/* int main()
{
	const char *str = "Test string";
	size_t length = ft_strlen(str);
	
	printf("The length of the string: %s is:%zu\n", str, length);
	return (0);	
} */