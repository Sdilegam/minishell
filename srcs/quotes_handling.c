/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:00:12 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/22 15:09:00 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_len(char *string)
{
	int		index;
	char	quote;
	
	index = 0;
	quote = string[0];
	while (string[++index])
	{
		if (string[index] == quote)
			return (index);
	}
	return (-1);
}

int	count_quotes(char *string, int len)
{
	int	index;
	int	count;

	count = 0;
	index = -1;
	while (++index <= len)
	{
		if (string [index] == '\'' || string [index] == '"')
		{
			count += 2;
			index += get_quote_len(string + index);
		}
	}
	return (count);
}

void	duplicate_quotes(char *str_to, char *str_from, t_env *env)
{
	int		index;
	int		index_from;
	char	quote;

	index = 0;
	index_from = 1;
	quote = str_from[0];
	while (str_from[index_from] != quote)
	{
		if (str_from[index_from] == '$' && quote == '"')
		{
			index += duplicate_var(str_to + index, str_from + index_from + 1, env);
			while (!is_space(str_from[index_from]) && str_from[index_from] && \
			str_from[index_from] != quote)
				index_from++;
		}
		if (str_from[index_from] != quote)
			str_to[index++] = str_from[index_from++];
	}
}
