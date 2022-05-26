/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:14:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/25 23:48:19 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env, int p)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		ft_printf("%s\n", curr->var);
		curr = curr->next;
	}
	if (p)
		free(curr);
}

void	ft_env(t_env *env, char **str)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	if (str[1])
	{
		while (str[1][i])
		{
			if (str[1][i] == '=')
				break ;
			i++;
		}
		if (str[1][i] != '=' || i == 0)
		{
			if (i == 0)
			{
				ft_printf("env : %s: Invalid argument\n", str[1]);
				return ;
			}
			ft_printf("env : %s: No such file or directory\n", str[1]);
			return ;
		}
		insertnewnode(env, str[1]);
		p = 1;
	}
	print_env(env, p);
}
