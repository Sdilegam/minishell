/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:04:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/28 14:25:24 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_variable(t_env *env, char *string, int len)
{
	t_env	*curr;

	curr = env;
	while (curr && string)
	{	
		if (ft_strncmp(curr->var, string, len) == 0)
			return (curr);
		curr = curr->next;
	}
	return (0);
}

int	get_variable_len(t_env var)
{
	return (ft_strlen(var.content) - ft_strlen(var.var) + 1);
}

int	duplicate_var(char *str_to, char *str_from, t_env *env)
{
	int		index;
	int		temp;
	t_env	*var;

	index = 0;
	temp = 0;
	while (str_from[temp] && !is_space(str_from[temp]) && str_from[temp] != '"')
		temp++;
	var = search_variable(env, str_from, temp);
	if (var)
	{
		while (var->content[index])
		{
			str_to[index] = var->content[index];
			index ++;
		}
	}
	return (index);
}

int	get_final_len(char *string, t_env *env, int len)
{
	int		index;
	int		final_len;
	int		temp;
	t_env	*var;

	index = -1;
	final_len = 0;
	while (++index < len)
	{
		if (string[index] == '\'')
			index += get_quote_len(string + index);
		if (string[index] == '$')
		{
			temp = 0;
			while (string[index + temp] && !is_space(string[index + temp]) && \
			string[index + temp] != '"')
				temp++;
			var = search_variable(env, string + index + 1, temp - 1);
			if (var)
			{
				index += ft_strlen(var->var) + 1;
				final_len += get_variable_len(*var);
			}
			else
				final_len -= temp;
		}
	}
	return (index - count_quotes(string, len) + final_len);
}
