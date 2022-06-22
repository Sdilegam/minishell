/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/22 13:49:34 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char chara)
{
	if (!chara)
		return (0);
	if (chara == ' ')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] && s2[index])
	{
		if ((unsigned char) s1[index] != (unsigned char) s2[index])
			break ;
		index++;
		if (index == n)
			return (0);
	}
	return ((unsigned char) s1[index] - (unsigned char) s2[index]);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
