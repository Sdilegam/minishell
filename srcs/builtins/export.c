/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 01:11:30 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/26 12:09:05 by abkasmi          ###   ########.fr       */
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
		return(ft_printf("export : %s: not a valid identifier\n", str));
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
	int		i;
	int		j;

	i = -1;
	j = 0;
	curr = env;
	while (str[++j])
	{
		if (export_error(str[j]))
			return ;
		while (str[j][++i])
			if (str[j][i] == '=')
				insertnewnode(env, str[j]);
		i = -1;
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
