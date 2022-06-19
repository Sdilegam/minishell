/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/19 16:27:57 by sdi-lega         ###   ########.fr       */
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
	while (++index < len)
	{
		if (string [index] == '\'' || string [index] == '"')
		{
			count += 1;
			index += get_quote_len(string);
		}
	}
	return (count);
}

void	duplicate_quotes(char *str_to, char *str_from)
{
	int		index;
	char	quote;

	index = 0;
	quote = str_from[0];
	while (str_from[++index] != quote)
	{
		str_to[index] = str_from[index];
	}
}


char	*duplicate_word(char *string, int len)
{
	int		index_to;
	int		index_from;
	char	*word;

	index_to = 0;
	index_from = 0;
	word = malloc(sizeof(char) * (len + 1 - count_quotes(string, len)));
	while (index_from != len)
	{
		if ((string [index] == '\'' || string [index] == '"'))
		{
			temp = get_quote_len(string + index) - 1;
			string ++;
		}
		if ((string [index] != '\'' && string [index] != '"') || temp > 0)
		{
			temp --;
			word[index] = string[index];
			index ++;
		}
	}
	word[index] = 0;
	return (word);
}

int	count_words(char *string)
{
	int	count;
	int	i;
	int	temp;

	i = 0;
	count = 0;
	while (string[i] && string[i] != '|')
	{
		if (!is_space(string[i]))
			count++;
		while (!is_space(string[i]) && string[i])
		{
			if (string[i] == '\'' || string[i] == '"')
			{
				temp = get_quote_len(string + i);
				if (temp == -1)
					return (0);
				i += temp;
			}
			i++;
		}
		while (is_space(string[i]) && string[i])
			i++;
	}
	return (count);
}

char	**read_line(char *string)
{
	int		i;
	int		temp;
	int		count;
	char	**line;
	int		index;

	i = 0;
	temp = 0;
	index = -1;
	count = count_words(string);
	line = malloc((count + 1) * sizeof(char *));
	line[count] = 0;
	while (++index < count)
	{	
		while (is_space(string[i]) && string[i])
			i++;
		while (!is_space(string[i + temp]) && string[i + temp])
		{
			if (string[i + temp] == '\'' || string[i + temp] == '"')
			{
				temp += get_quote_len(string + i + temp);
			}
			temp++;
		}
		line[index] = duplicate_word(string + i, temp);
		i += temp;
		temp = 0;
	}
	return (line);
}

/*
char	*parse_string(char *string, t_env *env)
{
	int	index;

	index = 0;
	while (string[index] && string[index] != '|')
	{
		while (is_space(string[index]) && string[index])
			index++;
		while (!is_space(string[index]))
			
	}
	return (0);
	
}

*/
