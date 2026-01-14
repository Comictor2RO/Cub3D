/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:15:25 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 11:55:45 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Description:
This function allocates memory for an array of num elements, each of size size,
and initializes all bytes in the allocated memory to zero.

Return Value:
This function returns a pointer to the allocated memory.
If the allocation fails, it returns NULL. */
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	t_size;
	void	*ptr;

	t_size = nmemb * size;
	if (nmemb != 0 && t_size / nmemb != size)
	{
		return (NULL);
	}
	ptr = malloc(t_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, t_size);
	return (ptr);
}
/* int main() 
{
    int *numbers = (int *)calloc(20, sizeof(int));

    if (numbers == NULL) 
	{
        printf("Error: Memory allocation failed.\n");
        return (1);
    }
    printf("numbers[0] = %d\n", numbers[0]);
    printf("numbers[1] = %d\n", numbers[1]);

    free(numbers);

    return (0);
} */