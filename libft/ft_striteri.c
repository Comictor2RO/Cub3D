/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:47:37 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:48:22 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // de facut main de test
/* Description:
Applies the function f to each character of the string s,
passing its index as the first argument.
Each character is passed by address to f,
allowing it to be modified if necessary.
Return Value: */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/* int main()
{
    char str[] = "hello world";  // Non-constant string so it can be modified
    printf("Original: %s\n", str);

    ft_striteri(str, ft_toupper);

    printf("Transformed: %s\n", str);

    return 0;
} */