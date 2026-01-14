/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:16:20 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:42:29 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function checks whether c is alphabetical (i.e., a letter) or not.

Return Value
This function returns a non-zero int if c is alphabetical
and 0 if c is not alphabetical.
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/* int main()
{
	char test1 = 'A';
	char test2 = '1';

	if (ft_isalpha(test1))
	{
		printf("%c is alphabetic character!\n",test1);
	}
	else 
	{
		printf("%c is not alphabetic character!\n",test1);
	}
	if (ft_isalpha(test2))
	{
		printf("%c is an alphabetic character!",test2);
	}
	else 
	{
		printf("%c is not an alphabetic character!",test2);
	}
	return 0;
} */