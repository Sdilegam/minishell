/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:14 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 10:52:02 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_shlvl(t_env *env)
{
	int		lvl;
	char	*lvl2;

	if (!env)
		return (1);
	while (env)
	{
		if (ft_strcmp("SHLVL", env->var) == 0 && env->var)
		{
			lvl = ft_atoi(env->content);
			lvl += 1;
			free(env->content);
			lvl2 = ft_itoa(lvl);
			if (!lvl2)
			{
				ft_free_env(env);
				ft_putstr("Malloc failed in check_shlvl\n", 2);
				exit(1);
			}
			env->content = lvl2;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
