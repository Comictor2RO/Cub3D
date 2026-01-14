/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:44:40 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/12 15:58:57 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function checks whether c is alphanumeric
(i.e., a letter or a number) or not.

Return Value:
his function returns a non-zero int if c is alphanumeric
and 0 if c is not alphanumeric. */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/* int main() 
{
    char c = 'A';
    
    if (ft_isalnum(c)) 
    
        printf("%c is alphanumeric.\n", c);
    else 
        printf("%c is not alphanumeric.\n", c);
   return (0);   
} */