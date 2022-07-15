/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:51 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 01:30:16 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *string, int index)
{
	int	count;
	int	offset;

	offset = 0;
	count = 0;
	while (index - ++offset > -1 && string[index - offset] && is_p_redi(&string[index - offset]) == 0)
		if (!is_space(string[index - offset]))
			count++;
	if (count == 0)
		return (1);
	count = 0;
	offset = 0;
	while (string[index + ++offset] && is_p_redi(&string[index + offset]) == 0)
		if (!is_space(string[index + offset]))
			count++;
	if (count == 0 && !string[index + offset])
		return (1);
	return (0);
}

static int	get_offset(char *string, int index)
{
	int	redi;

	redi = is_p_redi(string + index);
	if (redi >= 4)
		return (2);
	else
		return (1);
}

int	check_redi(char *string, int index)
{
	int	count;
	int	offset;

	offset = get_offset(string, index) - 1;
	count = 0;
	while (string[index + ++offset] && is_p_redi(&string[index + offset]) == 0)
		if (!is_space(string[index + offset]))
			count++;
	if (count == 0)
		return (offset);
	return (0);
}

int	err_redi(char *string, int offset, int which_redi)
{
	ft_putstr("minishell: syntax error near unexpected token `", 2);
	if (which_redi == 1)
		ft_putstr("|'", 2);
	else
	{
		if (is_p_redi(string + offset) != 0)
			write(2, string + offset, get_offset(string, offset));
		else
			ft_putstr("newline", 2);
	}
	ft_putstr("'\n", 2);
	return (0);
}

int	check_quotes(char *string)
{
	int	i;
	int	temp;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '"')
		{
			temp = get_quote_len(string + i);
			if (temp == -1)
			{
				ft_putstr("minishell: unexpected EOF while looking for matching `", 2);
				ft_putstr(string + i, 2);
				ft_putstr("'\nminishell: syntax error: unexpected end of file\n", 2);
				return (0);
			}
			i += temp;
		}
		i++;
	}
	return (1);
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
