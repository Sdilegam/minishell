/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:14 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 15:10:50 by abkasmi          ###   ########.fr       */
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
			env->content = malloc(sizeof(char) * ft_strlen(lvl2) + 1);
			if (!env->content)
			{
				free(env->var);
				return (1);
			}
			env->content = lvl2;
			return (0);
		}
		env = env->next;
	}
	return (0);
}