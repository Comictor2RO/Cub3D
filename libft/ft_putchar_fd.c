/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:51:48 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/12 16:09:42 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
The function uses the write system call to output the character c
to the file descriptor fd.

Return Value:
It writes exactly one byte (the character c). */
void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		fd *= -1;
	write(fd, &c, 1);
}
/* int main()
{
    char c = 'A';
    ft_putchar_fd(c, 1);
} */