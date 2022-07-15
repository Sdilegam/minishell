/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:19:26 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 10:21:28 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	not_allowed_char(char chara)
{
	if (chara == '\\' || chara == '(' || chara == ')' || chara == ';' \
	|| chara == '&' || chara == '*')
	{
		ft_putstr("'", 2);
		ft_putstr(&chara, 2);
		ft_putstr("' not allowed in this minishell.\n", 2);
		return (1);
	}
	return (0);
}

int	check_string(char *string)
{
	int	index;
	int	is_redi;
	int	offset;

	index = 0;
	while (string[index])
	{
		is_redi = is_p_redi(&string[index]);
		if (is_redi == 1)
			if (check_pipe(string, index) != 0)
				return (err_redi(string + index, 0, is_redi));
		if (is_redi > 1)
		{
			offset = check_redi(string, index);
			if (offset > 0)
				return (err_redi(string + index, offset, is_redi));
		}
		if (not_allowed_char(string[index]) == 1)
			return (0);
		index += get_offset(string, index);
	}
	if (check_quotes(string) == 0)
		return (0);
	return (1);
}
