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
		tmp = comm->next;
		while (comm->parameters[++i])
			free(comm->parameters[i]);
		free(comm->parameters);
		free(comm);
		comm = tmp;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		if (env->content)
			free(env->content);
		if (env->var)
			free(env->var);
		free (env);
		env = temp;
	}
}

void	ft_free_all(t_env *env, t_comm *comm)
{
	ft_free_env(env);
	ft_free_comm(comm);
	rl_clear_history();
}
