/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:11:38 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:50:15 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function checks whether c is a printable character,
including space, or not.

Return Value:
This function returns a non-zero int if c is a printable 
character and 0 if c is not a printable character. */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/* int	main()
{
	char c = '$';

	if (ft_isprint(c))
		printf("%c is a printable character!\n", c);
	else
		printf("%c is not a printable character!\n", c);
	return (0);
} */