/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 01:11:30 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 14:28:17 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ok(char chara)
{
	if (('a' <= chara && chara <= 'z') || \
	('A' <= chara && chara <= 'Z') || \
	('0' <= chara && chara <= '9') || \
	(chara == '_') || chara == '=')
		return (1);
	return (0);
}

int	export_error(char *str)
{
	int	index;

	index = 0;
	if (('0' <= str[0] && str[0] <= '9') || str[index] == '=')
	{
		ft_putstr("export: ", 2);
		ft_putstr(str, 2);
		ft_putstr(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[index] && str[index] != '=')
	{
		if (!is_ok(str[index]))
		{
			ft_putstr("export: ", 2);
			ft_putstr(str, 2);
			ft_putstr(": not a valid identifier\n", 2);
			return (1);
		}
		index++;
	}
	return (0);
}

void	export2(t_env *env, t_env *curr, t_var var)
{
	int	exist;

	exist = 0;
	while (curr && var.name)
	{	
		if (ft_strcmp(curr->var, var.name) == 0)
		{	
			free(curr->content);
			free(var.name);
			curr->content = var.content;
			exist = 1;
			break ;
		}
		curr = curr->next;
	}
	if (var.name && !exist)
		insertnewnode(env, var.name, var.content);
}

void	ft_print(t_env *curr)
{
	while (curr)
	{
		ft_printf("declare -x %s=%s\n", curr->var, curr->content);
		curr = curr->next;
	}
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
		{
			g_status.status = 1 << 8;
			return ;
		}
		export2(env, curr, var);
		curr = env;
	}
	if (!str[1])
		ft_print(curr);
	g_status.status = 0 << 8;
}
