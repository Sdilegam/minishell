/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 01:11:30 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/22 13:07:18 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ok(char chara)
{
	if (('a' <= chara && chara <= 'z') || \
	('A' <= chara && chara <= 'Z') || \
	('0' <= chara && chara <= '9') || \
	(chara == '_'))
		return (1);
	return (0);
}

int	export_error(char *str)
{
	int	index;

	index = 0;
	if (('0' <= str[0] && str[0] <= '9') || str[index] == '=')
		return (ft_printf("export : %s: not a valid identifier\n", str));
	while (str[index] && str[index] != '=')
	{
		if (!is_ok(str[index]))
			return (ft_printf("export : %s: not a valid identifier\n", str));
		index++;
	}
	return (0);
}

void	ft_export(t_env *env, char **str)
{
	t_env	*curr;
	int		j;
	t_var	var;

	j = 0;
	curr = env;
	while (str[++j])
	{
		var.name = ft_cpy_name(str[j]);
		var.content = ft_cpy_content(str[j]);
		if (export_error(str[j]))
			return ;
		curr = search_variable(env, var.name, ft_strlen(var.name));
		if (curr && var.name)
		{
			free(curr->content);
			curr->content = var.content;
		}
		else if (var.name)
			insertnewnode(env, var.name, var.content);
		curr = env;
	}
	if (!str[1])
	{
		while (curr)
		{
			ft_printf("declare -x %s\n", curr->var);
			curr = curr->next;
		}
	}
}
