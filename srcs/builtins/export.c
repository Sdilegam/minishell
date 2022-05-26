/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 01:11:30 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/26 04:11:40 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_env *env, char **str)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = env;
	if (str[1])
	{
		while (str[1][i])
		{
			if (str[1][i] == '=')
			{
				if (i == 0)
				{
					ft_printf("export : %s: not a valid identifier\n", str[1]);
					return ;
				}
				insertnewnode(env, str[1]);
				return ;
			}
			else if ((str[1][i] > 64 && str[1][i] < 91)
				|| (str[1][i] > 96 && str[1][i] < 123))
				
			i++;
		}
		if (str[1][i] != '=')
			return ;
	}
	while (curr)
	{
		ft_printf("declare -x %s\n", curr->var);
		curr = curr->next;
	}
}