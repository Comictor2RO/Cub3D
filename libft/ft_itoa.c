/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:53:12 by ggabor            #+#    #+#             */
/*   Updated: 2025/01/10 12:47:22 by ggabor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // de facut main si reverificat codul 

static int	count_digit(int n)
{
	int	count;

	if (n <= 0)
		count = 1;
	else
		count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/* Description:
This function converts an integer value into a null-terminated string based
on the specified base and stores the result in the array pointed to by str.
The base can range from 2 to 36.

Return Value:
This function returns a pointer to the resulting string, str */
char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;

	len = count_digit(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}
/* int main()
{
    int numbers[] = {123, -456, 0, 7890, -12345};
    int i;

    for (i = 0; i < 5; i++)
    {
        char *str = ft_itoa(numbers[i]);
        if (str)
        {
            printf("Number: %d, String: %s\n", numbers[i], str);
            free(str);  // Don't forget to free the allocated memory
        }
        else
        {
            printf("Error allocating memory\n");
        }
    }

    return 0;
} */