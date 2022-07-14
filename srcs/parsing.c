/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/14 19:19:07 by sdi-lega         ###   ########.fr       */
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
			word[index_to++] = string[index_from++];
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

char	**read_line(char *string, t_env *env, t_comm *comm)
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
	if (!line)
		ft_free_malloc_err(env, comm);
	line[count] = 0;
	while (++index < count)
	{	
		while (is_space(string[i]) && string[i] && is_p_redi(string + i) == 0)
			i++;
		while (!is_space(string[i + temp]) && string[i + temp]
			&& is_p_redi(string + i) == 0)
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

t_comm	*parse_parameters(char *string, t_env *env)
{
	t_comm	*command;
	t_comm	*cursor;
	char	*temp;
	int		(*temp_func)(struct s_comm *first, struct s_env *env);
	int		i;

	if (check_string(string) == 0)
	{
		g_status.status = 2 << 8;
		return (0);
	}
	i = where_is_pipe(string);
	temp = replace_dollars(string, env, i, NULL);
	command = create_command(read_line(temp, env, NULL));
	if (!command)
		ft_free_malloc_err(env, command);
	free(temp);
	temp_func = set_comm(string + i);
	cursor = command;
	while (string[i])
	{
		string += i + get_redi_len(string + i);
		i = where_is_pipe(string);
		temp = replace_dollars(string, env, i, command);
		add_command(command, create_command(read_line(temp, env, command)));
		free (temp);
		cursor = cursor->next;
		cursor->func = temp_func;
		temp_func = set_comm(string + i);
	}
	return (command);
}
