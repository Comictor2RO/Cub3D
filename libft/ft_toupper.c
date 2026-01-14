/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:32:10 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:43:04 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function converts c to uppercase.

Return Value:
If c is a lowercase letter (a through z), this function returns
its uppercase equivalent (A through Z).
If c is not a lowercase letter, this function returns c itself. */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/* int	main()
{
	char c = 'a';
	
	printf("%c to uppercase is: %c\n", c, ft_toupper(c));
	return (0);
} */