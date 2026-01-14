/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:50:41 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:46:54 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function checks whether c is an ASCII character
(i.e., a value between 0 and 127 inclusive) or not.

Return Value:
Returns a non-zero int if c is an ASCII character
and 0 if c is not an ASCII character. */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* int	main()
{
	char c = 128;
	
	if(ft_isascii(c))
		printf("%c is an ASCII character!\n", c);
	else	
		printf("%c is not an ASCII character\n",c);
	return (0);
} */