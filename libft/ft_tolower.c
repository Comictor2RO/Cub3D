/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:37:09 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:43:24 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function converts c to lowercase.

Return Value:
If c is an uppercase letter (A through Z), this function returns
its lowercase equivalent (a through z).
If c is not an uppercase letter, this function returns c itself. */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/* int	main()
{
	char c = 'Z';
	
	printf("%c to lowercase is:%c\n", c, ft_tolower(c));
	return (0);
} */