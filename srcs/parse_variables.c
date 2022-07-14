/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:04:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/14 03:07:11 by sdi-lega         ###   ########.fr       */
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
	int		index_from;
	int		temp;
	t_env	*var;
	char	*errcode;

	index_from = -1;
	temp = 0;
	while (str_from[temp] && !is_space(str_from[temp])
		&& str_from[temp] != '"' && str_from[temp] != '\'')
		temp++;
	var = search_variable(env, str_from, temp);
	if (ft_strncmp("?", str_from, temp) == 0)
	{
		errcode = ft_itoa(g_status.status >> 8);
		while (errcode[++index_from])
			str_to [index_from] = errcode [index_from];
		free(errcode);
	}
	if (var)
	{
		while (var->content[++index_from])
			str_to[index_from] = var->content[index_from];
	}
	return (index_from);
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

int	get_errcode(char *string)
{
	int		index;
	char	*errcode;

	index = -1;
	errcode = ft_itoa(g_status.status << 8);
	while (errcode[++index])
		string [index] = errcode [index];
	free(errcode);
	return (index);
}

char	*replace_dollars(char *base_str, t_env *env, int len)
{
	int		index_to;
	int		index_from;
	char	*str_to;
	int		new_len;
	int		quote;

	index_to = -1;
	quote = 0;
	new_len = get_final_len(base_str, env, len);
	index_from = -1;
	str_to = calloc(new_len + 1, sizeof(char));
	while (++index_from < len)
	{
		if (base_str[index_from] == '\'' && quote % 2 == 0)
		{
			str_to[++index_to] = '\'';
			duplicate_quotes(str_to + index_to +1, base_str + index_from);
			index_to += get_quote_len(base_str + index_from) - 1;
			str_to[++index_to] = '\'';
			index_from += get_quote_len(base_str + index_from) + 1;
		}
		if (base_str[index_from] == '"')
			quote ++;
		if (base_str [index_from] == '$')
		{
			index_to += duplicate_var(str_to + index_to + 1,
					base_str + index_from + 1, env);
			while (!is_space(base_str[index_from]) && base_str[index_from]
				&& base_str[index_from] != '"' && base_str[index_from] != '\'')
				index_from++;
		}
		if (base_str[index_from])
			str_to [++index_to] = base_str[index_from];
	}
	str_to[++index_to] = '\0';
	return (str_to);
}
