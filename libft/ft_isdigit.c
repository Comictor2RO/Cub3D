/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:27:41 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:48:21 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function checks whether c is a decimal digit
('0' through '9') or not.
In other words, it checks whether the ASCII value
of c is between 48 and 57, inclusive.
Return Value:
This function returns a non-zero int if c
is a decimal digit and 0 if c is not a decimal digit. */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* int main()
{
	char c = 'A';
		
	if (ft_isdigit(c))
	
		printf("%c is digit!\n", c);
	else
		printf("%c is not digit!\n", c);
	return 0;
} */