/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/28 03:56:01 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicate_word(char *string, int len, t_env *env)
{
	int		index_to;
	int		index_from;
	int		temp;
	char	*word;

	index_to = 0;
	index_from = 0;
	word = calloc(sizeof(char), get_final_len(string, env, len));
	while (index_from < len)
	{
		if ((string [index_from] == '\'' || string [index_from] == '"'))
		{
			temp = get_quote_len(string + index_from);
			duplicate_quotes(word + index_to, string + index_from, env);
			index_from +=temp + 1;
			while (word[index_to])
				index_to ++;
		}
		if (string [index_from] == '$')
		{
			index_to += duplicate_var(word + index_to, string + index_from + 1, env);
			while (!is_space(string[index_from]) && string[index_from])
				index_from++;
		}
		else if (index_from < len)
			word[index_to++] = string[index_from++];
	}
	word[index_to] = 0;
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

char	**read_line(char *string, t_env *env)
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
		line[index] = duplicate_word(string + i, temp, env);
		i += temp;
		temp = 0;
	}
	return (line);
}

t_comm	*parse_parameters(char *string, t_env *env)
{
	t_comm	*command;
	t_comm	*cursor;
	int		i;

	command = create_command(read_line(string, env));
	if (!*(command->parameters))
		return (0);
	i = where_is_pipe(string);
	command->func = &function;
	cursor = command;
	while (i)
	{
		string += i + 1;
		cursor->func = &ft_pipe;
		add_command(command, create_command(read_line(string, env)));
		if (!*(cursor->next->parameters))
			return (0);
		cursor = cursor->next;
		cursor->func = &function;
		i = where_is_pipe(string);
	}
	return (command);
}
