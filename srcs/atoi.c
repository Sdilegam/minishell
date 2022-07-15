/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:04:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 14:49:37 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	ft_overflow(const char *str, int signe, int i)
{
	unsigned long long	num;

	num = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		num = (num * 10) + (str[i] - 48);
		if (num >= LONG_MAX && signe == 1)
			return (-1);
		else if (num > LONG_MAX && signe == -1)
			return (0);
		i++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	signe;

	i = 0;
	signe = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	num = ft_overflow(str, signe, i);
	return (num * signe);
}
