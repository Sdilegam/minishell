/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:26:12 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/12 16:26:23 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_var(char *string, char *var)
{
	int	count;
	int	i;
	int	temp;

	count = 0;
	i = 0;
	if (!is_space(string [-1]))
		count--;
	while (var[i])
	{
		temp = 0;
		while (is_space(string[i]))
			i++;
		if (!is_space(string[i]))
			count++;
		while (!is_space(string[i]))
		{
			if (string[i] == '\'' || string[i] == '"')
			{
				temp = get_quote_len(string + i);
				if (temp == -1)
					return (0);
				i += temp;
			}
			else
				i++;
		}
	}
	return (count);
}

int	main(int argc, char *argv[])
{
	int	index;
	char *string;
	char *var;
	int	count;

	index = 0;
	count = 0;
	if (argc != 3)
		return (1);
	string = argv[1];
	var = argv[2];
	while (string[index])
	{
		while (is_space(string[index]))
			index ++;
		if (!is_space(string[index]) && string[index])
		{
			count ++;
			while (!is_space(string[index]) && string[index])
			{
				if (string[index] == '$')
				{
					count += handle_var(string, var);
					while (!is_space(string[index]) && string[index])
					{
						index ++;
					}
				}
				else if (string[index] == '\'' || string[index] == '"')
				{
					index += count_quotes(string, ft_strlen(string));
				}
				else
					index ++;
			}
		}
	}
	printf ("count: %d\n", count);
	return (0);
}
