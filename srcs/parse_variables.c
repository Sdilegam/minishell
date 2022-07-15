/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:04:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 11:51:02 by sdi-lega         ###   ########.fr       */
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

int	get_errcode(char *string, t_env *env)
{
	int		index;
	char	*errcode;

	index = -1;
	errcode = ft_itoa(g_status.status >> 8);
	if (!errcode)
		ft_free_malloc_err(env, NULL);
	while (errcode[++index])
		string [index] = errcode [index];
	free(errcode);
	return (index);
}

int	duplicate_var(char *str_to, char *str_from, t_env *env)
{
	int		index;
	int		var_len;
	t_env	*var;

	index = -1;
	var_len = var_id_len(str_from);
	var = search_variable(env, str_from, var_len);
	if (ft_strncmp("?", str_from, var_len) == 0)
		return (get_errcode(str_to, env));
	else if (var)
	{
		str_to[++index] = -5;
		while (var->content[++index - 1])
			str_to[index] = var->content[index - 1];
		str_to[index] = -5;
	}
	return (index + 1);
}

void	rewrite_squotes(char *str_to, char *base_str, int index[2])
{
	int	temp;

	temp = 0;
	base_str += index[0];
	str_to += index[1] + 1;
	str_to[temp] = '\'';
	while (base_str[++temp] != '\'')
				str_to [temp] = base_str[temp];
	str_to[temp] = '\'';
	index[1] += temp + 1;
	index[0] += temp;
}

char	*replace_dollars(char *base_str, t_env *env, int len, t_comm *comm)
{
	int		i[2];
	char	*str_to;
	int		quote;

	i[1] = -1;
	quote = 0;
	i[0] = -1;
	str_to = ft_calloc(get_final_len(base_str, env, len) + 1, sizeof(char));
	if (!str_to)
		ft_free_malloc_err(env, comm);
	while (++i[0] < len)
	{
		if (base_str[i[0]] == '\'' && quote % 2 == 0)
			rewrite_squotes(str_to, base_str, i);
		else if (base_str [i[0]] == '$')
		{
			i[1] += duplicate_var(str_to + i[1] + 1, base_str + i[0] + 1, env);
			i[0] += var_id_len(base_str + i[0] + 1);
		}
		else if (i[0] < len)
			str_to [++i[1]] = base_str[i[0]];
		if (base_str[i[0]] == '"')
			quote ++;
	}
	return (str_to);
}
