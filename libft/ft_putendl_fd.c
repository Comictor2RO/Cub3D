/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:58:12 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/12 16:17:03 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function writes the string s followed by a newline (\n)
to the file descriptor fd.
Return Value: */
void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0)
		fd *= -1;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
/* int main()
{
    char str[] = "Hello, world!";
    ft_putendl_fd(str, 1); 
	return (0);
} */