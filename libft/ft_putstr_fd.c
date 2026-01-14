/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:55:04 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/12 16:09:56 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // de facut main de test
/* Description:
This function writes the string s to the file descriptor fd.
It outputs each character of the string in sequence
until it reaches the null terminator (\0).
Return Value: */
void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0)
		fd *= -1;
	write(fd, s, ft_strlen(s));
}
/* int main()
{
    char str[] = "Hello, world!";
    
    ft_putstr_fd(str, 1);
    return (0);
} */