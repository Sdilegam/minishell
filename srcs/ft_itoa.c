/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:39:41 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 23:48:44 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_int(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
		while (n > 9)
		{
			n /= 10;
			count++;
		}
		return (count);
	}
	else if (n > 0)
	{
		while (n > 9)
		{
			n /= 10;
			count++;
		}
		return (count);
	}
	return (count);
}

static char	*ft_int_to_array(int count, int n, char *str, int signe)
{
	while (n > 9)
	{
		str[count] = (n % 10) + 48;
		n = n / 10;
		count--;
	}
	str[count] = n + 48;
	if (signe == -1)
		str[--count] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char				*str;
	int					count;
	int					signe;

	signe = 1;
	count = len_int(n);
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		signe = -1;
		n = -n;
	}
	str[count] = '\0';
	count--;
	return (ft_int_to_array(count, n, str, signe));
}
