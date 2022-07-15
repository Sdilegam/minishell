/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 13:41:27 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicate_word(char *str, int len, int *quotes)
{
	int		i_to;
	int		i_from;
	char	*word;

	i_to = 0;
	i_from = 0;
	word = ft_calloc(sizeof(char), len - count_quotes(str, len) + 1);
	while (i_from < len)
	{
		if ((str [i_from] == '\'' || str [i_from] == '"') && *quotes % 2 == 0)
		{
			duplicate_quotes(word + i_to, str + i_from);
			i_from += get_quote_len(str + i_from) + 1;
			while (word[i_to])
				i_to ++;
		}
		else if (i_from < len)
		{
			if (str[i_from] == -5)
				*quotes += (++i_from * 0) + 1;
			else
				word[i_to++] = str[i_from++];
		}
	}
	return (word);
}

int	count_words(char *string, int *quotes)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (!is_space(string[i]))
			count++;
		while (!is_space(string[i]) && string[i])
		{
			if ((string[i] == '\'' || string[i] == '"') && *quotes % 2 == 0)
				i += get_quote_len(string + i);
			if (string[i] == -5)
				*quotes += 1;
			i++;
		}
		while (is_space(string[i]) && string[i])
			i++;
	}
	*quotes = 0;
	return (count);
}

char	*parse_word(char *str, int	*index, int *quotes)
{
	int		tmp;
	int		i;
	char	*word;

	tmp = 0;
	i = *index;
	while (!is_space(str[i + tmp]) && str[i + tmp])
	{
		if ((str[i + tmp] == '\'' || str[i + tmp] == '"') && *quotes % 2 == 0)
			tmp += get_quote_len(str + i + tmp);
		if (str[i + tmp] == -5)
			*quotes += 1;
		tmp++;
	}
	*quotes = 0;
	word = duplicate_word(str + i, tmp, quotes);
	*index += tmp;
	return (word);
}

char	**read_line(char *string, t_env *env, t_comm *comm)
{
	int		i;
	int		count;
	char	**line;
	int		index;
	int		quotes;

	i = 0;
	index = -1;
	quotes = 0;
	count = count_words(string, &quotes);
	line = ft_calloc((count + 1), sizeof(char *));
	if (!line)
		ft_free_malloc_err(env, comm);
	while (++index < count)
	{	
		while (is_space(string[i]) && string[i])
			i++;
		line[index] = parse_word(string, &i, &quotes);
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
