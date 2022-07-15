/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 02:08:48 by sdi-lega         ###   ########.fr       */
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

int	get_redi_len(char *string)
{
	if (*string == '<' && *(string + 1) == '<')
		return (2);
	if (*string == '>' && *(string + 1) == '>')
		return (2);
	if (*string == '>' && *(string + 1) == '|')
		return (2);
	else
		return (1);
}

void	parse_new_coms(char *string, int i, t_comm *first_com, t_env *env)
{
	int		(*temp_func)(struct s_comm *first, struct s_env *env);
	char	*temp;
	t_comm	*cursor;

	cursor = first_com;
	while (string[i])
	{
		temp_func = set_comm(string + i);
		string += i + get_redi_len(string + i);
		i = where_is_pipe(string);
		temp = replace_dollars(string, env, i, first_com);
		add_command(first_com, create_command(read_line(temp, env, first_com)));
		free (temp);
		cursor = cursor->next;
		if (!cursor)
			ft_free_malloc_err(env, cursor);
		cursor->func = temp_func;
	}
	return ;
}

t_comm	*parse_parameters(char *string, t_env *env)
{
	t_comm	*first_com;
	char	*temp;
	int		i;

	if (check_string(string) == 0)
	{
		g_status.status = 2 << 8;
		return (0);
	}
	i = where_is_pipe(string);
	temp = replace_dollars(string, env, i, NULL);
	first_com = create_command(read_line(temp, env, NULL));
	free(temp);
	if (!first_com)
		ft_free_malloc_err(env, first_com);
	parse_new_coms(string, i, first_com, env);
	return (first_com);
}
