/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 10:20:16 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicate_word(char *string, int len)
{
	int		index_to;
	int		index_from;
	int		temp;
	char	*word;

	index_to = 0;
	index_from = 0;
	word = ft_calloc(sizeof(char), len - count_quotes(string, len) + 1);
	while (index_from < len)
	{
		if ((string [index_from] == '\'' || string [index_from] == '"'))
		{
			temp = get_quote_len(string + index_from);
			duplicate_quotes(word + index_to, string + index_from);
			index_from += temp + 1;
			while (word[index_to])
				index_to ++;
		}
		else if (index_from < len)
		{
			if (string[index_from] == '(' || string[index_from] == ')')
				index_from ++;
			else
				word[index_to++] = string[index_from++];
		}
	}
	return (word);
}

int	count_words(char *string)
{
	int	count;
	int	i;
	int	temp;

	i = 0;
	count = 0;
	while (string[i] && is_p_redi(string + i) == 0)
	{
		if (!is_space(string[i]))
			count++;
		while (!is_space(string[i]) && string[i] && is_p_redi(string + i) == 0)
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

char	*parse_word(char *str, int	*index)
{
	int		tmp;
	int		i;
	char	*word;

	tmp = 0;
	i = *index;
	while (!is_space(str[i + tmp]) && str[i + tmp] && is_p_redi(str + i) == 0)
	{
		if (str[i + tmp] == '\'' || str[i + tmp] == '"')
			tmp += get_quote_len(str + i + tmp);
		tmp++;
	}
	word = duplicate_word(str + i, tmp);
	*index += tmp;
	return (word);
}

char	**read_line(char *string, t_env *env, t_comm *comm)
{
	int		i;
	int		count;
	char	**line;
	int		index;

	i = 0;
	index = -1;
	count = count_words(string);
	line = ft_calloc((count + 1), sizeof(char *));
	if (!line)
		ft_free_malloc_err(env, comm);
	while (++index < count)
	{	
		while (is_space(string[i]) && string[i] && is_p_redi(string + i) == 0)
			i++;
		line[index] = parse_word(string, &i);
	}
	return (line);
}

int	(*set_comm(char *chara))(t_comm *comm, t_env *env)
{
	char	which_function;

	which_function = is_p_redi(chara);
	if (which_function == 1)
		return (&ft_pipe);
	if (which_function == 2)
		return (&ft_output_redir);
	if (which_function == 3)
		return (&input_redir);
	if (which_function == 4)
		return (&ft_delimiter_redir);
	if (which_function == 5)
		return (&ft_output_redir_append);
	else
		return (&function);
}
