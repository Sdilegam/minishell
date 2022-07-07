/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:04:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/07 06:40:23 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_variable(t_env *env, char *string, int len)
{
	t_env	*curr;

	curr = env;
	while (curr && string && len != 0)
	{	
		if (ft_strncmp(curr->var, string, len) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	get_variable_len(t_env var)
{
	return (ft_strlen(var.content) - ft_strlen(var.var));
}

int	duplicate_var(char *str_to, char *str_from, t_env *env)
{
	int		index_to;
	int		index_from;
	int		temp;
	t_env	*var;

	index_to = 0;
	index_from = 0;
	temp = 0;
	while (str_from[temp] && !is_space(str_from[temp]) && str_from[temp] != '"')
		temp++;
	var = search_variable(env, str_from, temp);
	if (var)
	{
		while (var->content[index_from])
		{
			if (0 < is_p_redi(&var->content[index_from]) && is_p_redi(&var->content[index_from]) < 4)
			{
				str_to[index_to++] = '"';
				str_to[index_to++] = var->content[index_from++];
				str_to[index_to++] = '"';
			}
			else if (3 < is_p_redi(&var->content[index_from]) && is_p_redi(&var->content[index_from]) < 6)
			{
				str_to[index_to++] = '"';
				str_to[index_to++] = var->content[index_from++];
				str_to[index_to++] = var->content[index_from++];
				str_to[index_to++] = '"';
			}
			else
			{
				str_to[index_to] = var->content[index_from];
				index_to ++;
				index_from ++;
			}
		}
	}
	return (index_to);
}
int	count_p_redi(char *string)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
	while (string[++index])
		if (is_p_redi(&string[index]) != 0)
			count++;
	return (count * 2);
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
				final_len += get_variable_len(*var) - 1 + count_p_redi(var->content);
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
	int		len;

	index_to = -1;
	len = get_final_len(base_str, env, ft_strlen(base_str) + 1);
	index_from = -1;
	str_to = calloc(len, sizeof(char));
	while (base_str[++index_from])
	{
		if (base_str[index_from] == '\'')
		{
			str_to[++index_to] = '\'';
			duplicate_quotes(str_to + index_to +1, base_str+index_from);
			index_to += get_quote_len(base_str+index_from) -1;
			str_to[++index_to] = '\'';
			index_from += get_quote_len(base_str+index_from) + 1;
		}
		if (base_str [index_from] == '$')
		{
			index_to += duplicate_var(str_to + index_to + 1, base_str + index_from + 1, env);
			while (!is_space(base_str[index_from]) && base_str[index_from] && base_str[index_from] != '"')
				index_from++;
		}
		if (base_str[index_from])
			str_to [++index_to] = base_str[index_from];
	}
	str_to[len - 1] = '\0';
	return (str_to);
}
