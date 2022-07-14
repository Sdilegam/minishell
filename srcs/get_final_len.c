/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:36:36 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 02:58:51 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	check(char *string, int index, int quote)
{
	if (string[index] == '\'' && quote % 2 == 0)
		if (get_quote_len(string + index) != -1)
			index += get_quote_len(string + index);
	if (string[index] == '"')
		quote ++;
}

int	len_loop(int index, char *string, int final_len, t_env *env)
{
	int		quote;
	int		temp;
	t_env	*var;

	quote = 0;
	check(string, index, quote);
	if (string[index] == '$')
	{
		temp = 0;
		while (string[index + temp] && !is_space(string[index + temp]) && \
			string[index + temp] != '"' && string[index + temp] != '\'')
			temp++;
		var = search_variable(env, string + index + 1, temp - 1);
		if (ft_strncmp(string + index + 1, "?", temp - 1) == 0)
			final_len += ft_strlen(ft_itoa(g_status.status)) - 2;
		else if (var)
			final_len += get_variable_len(*var) - 1
				+ count_p_redi(var->content);
		else
			final_len -= temp;
		index += temp;
	}
	return (final_len);
}

int	get_final_len(char *string, t_env *env, int len)
{
	int		final_len;
	int		index;
	char	quote;

	index = -1;
	final_len = 0;
	quote = 0;
	while (++index < len)
		final_len += len_loop(index, string, final_len, env);
	return (index + final_len);
}*/

int	get_final_len(char *string, t_env *env, int len)
{
	int		final_len;
	int		index;
	int		temp;
	t_env	*var;
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
			temp = 0;
			while (string[index + temp] && !is_space(string[index + temp]) && 
			string[index + temp] != '"' && string[index + temp] != '\'')
				temp++;
			var = search_variable(env, string + index + 1, temp - 1);
			if (ft_strncmp(string + index + 1, "?", temp - 1) == 0)
				final_len += ft_strlen(ft_itoa(g_status.status)) - 2;
			else if (var)
				final_len += get_variable_len(*var) - 1
					+ count_p_redi(var->content);
			else
				final_len -= temp;
			index += temp -1;
		}
	}
	return (index + final_len);
}
