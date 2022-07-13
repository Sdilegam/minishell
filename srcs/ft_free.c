/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 21:51:59 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 21:51:59 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_comm(t_comm *comm)
{
	int		i;
	t_comm	*tmp;

	while (comm)
	{
		i = -1;
		tmp = comm;
		while (tmp->parameters[++i])
			free(tmp->parameters[i]);
		free(tmp->parameters);
		free(tmp);
		comm = comm->next;
	}
}

void	ft_free_env(t_env *env)
{
	while (env)
	{
		if (env->content)
			free(env->content);
		if (env->var)
			free(env->var);
		env = env->next;
	}
	free(env);
}