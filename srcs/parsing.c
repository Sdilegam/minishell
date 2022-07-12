/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:37:44 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/12 16:05:34 by abkasmi          ###   ########.fr       */
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
	word = calloc(sizeof(char), len - count_quotes(string, len));
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

void	set_comm(char *chara, t_comm *comm)
{
	char	which_function;

	which_function = is_p_redi(chara);
	if (which_function == 0)
		comm->func = &function;
	if (which_function == 1)
		comm->func = &ft_pipe;
	if (which_function == 2)
		comm->func = &outp_redir;
	if (which_function == 3)
		comm->func = &input_redir;
	if (which_function == 4)
		comm->func = &ft_delimiter_redir;
	if (which_function == 5)
		comm->func = &outp_redir_append;
	return ;
}

t_comm	*parse_parameters(char *string, t_env *env)
{
	t_comm	*command;
	t_comm	*cursor;
	char	*temp;
	int		i;

	i = where_is_pipe(string);
	temp = replace_dollars(string, env, i);
	command = create_command(read_line(temp));
	free (temp);
	if (!*(command->parameters))
		return (0);
	set_comm(string + i, command);
	cursor = command;
	while (string[i])
	{
		string += i + 2;
		add_command(command, create_command(read_line(string)));
		if (!*(cursor->next->parameters))
			return (0);
		cursor = cursor->next;
		cursor->func = &function;
		i = where_is_pipe(string);
	}
	return (command);
}
