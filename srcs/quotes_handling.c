/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:00:12 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 14:15:36 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_len(char *string)
{
	int		index;
	int		var;
	char	quote;

	index = 0;
	quote = string[0];
	var = 0;
	while (string[++index])
	{
		if (string[index] == quote && var % 2 == 0)
			return (index);
		if (string[index] == -5)
			var ++;
	}
	return (-1);
}

int	count_quotes(char *string, int len)
{
	int	index;
	int	count;
	int	q;

	count = 0;
	index = -1;
	q = 0;
	while (++index <= len)
	{
		if ((string [index] == '\'' || string [index] == '"') && q % 2 == 0)
		{
			count += 2;
			index += get_quote_len(string + index);
		}
		if (string [index] == -5)
		{
			count += 1;
			q ++;
		}
	}
	return (count);
}

void	duplicate_quotes(char *str_to, char *str_from)
{
	int		index;
	int		index_from;
	char	quote;
	int		temp;

	index = 0;
	index_from = 1;
	quote = str_from[0];
	while (str_from[index_from] != quote)
	{
		if (str_from[index_from] == -5)
		{
			temp = 0;
			duplicate_quotes(str_to + index, str_from + index_from);
			while (str_to[index + temp])
				temp ++;
			index += temp;
			index_from += temp +2;
		}
		else
			str_to[index++] = str_from[index_from++];
	}
}
