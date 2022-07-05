/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:04:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/05 12:12:09 by abkasmi          ###   ########.fr       */
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
		if (ft_strncmp("?", string, len) == 0)
		{
			while (ft_strcmp("?", string) != 0)
				curr = curr->next;
			if (ft_strcmp("?", string) == 0)	
				curr->content = ft_itoa(g_status.status);
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
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
	return (index + final_len);
}

char	*replace_dollars(char *base_str, t_env *env)
{
	int		index_to;
	int		index_from;
	char	*str_to;

	index_to = -1;
	index_from = -1;
	str_to = calloc(get_final_len(base_str, env, where_is_pipe(base_str)), sizeof(char));
	while (base_str[++index_from] && base_str[index_from] != '|')
	{
		if (base_str [index_from] == '$')
		{
			index_to += duplicate_var(str_to + index_to + 1, base_str + index_from + 1, env);
			while (!is_space(base_str[index_from]) && base_str[index_from])
				index_from++;
		}
		else
			str_to [++index_to] = base_str[index_from];
	}
	return (str_to);
}
