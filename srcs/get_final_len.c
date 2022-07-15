/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:36 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 01:27:17 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_content_len(char *string, t_env *env, int id_len)
{
	t_env	*var;

	var = search_variable(env, string, id_len);
	if (ft_strncmp(string, "?", id_len) == 0)
		return (len_int(g_status.status >> 8) - 2);
	if (var)
		return (ft_strlen(var->content) - ft_strlen(var->var) + 1);
	else
		return (-(id_len + 1));
}

int	var_id_len(char *string)
{
	int	index;

	index = 0;
	while (string[index] && !is_space(string[index]) && string[index] != '"'\
			&& string[index] != '\'' && string[index] != '$')
		index ++;
	return (index);
}

int	get_final_len(char *string, t_env *env, int len)
{
	int		final_len;
	int		index;
	int		var_len;
	char	quote;

	index = -1;
	final_len = 0;
	quote = 0;
	while (++index < len)
	{
		if (string[index] == '\'' && quote % 2 == 0)
			if (get_quote_len(string + index) != -1)
				index += get_quote_len(string + index);
		if (string[index] == '"')
			quote ++;
		if (string[index] == '$')
		{
			var_len = var_id_len(string + index + 1);
			final_len += var_content_len(string + index + 1, env, var_len);
			index += var_len;
		}
	}
	return (index + final_len);
}
