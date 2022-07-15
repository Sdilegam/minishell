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

void	ft_free_malloc_err(t_env *env, t_comm *comm)
{
	if (env)
		ft_free_env(env);
	if (comm)
		ft_free_comm(comm);
	rl_clear_history();
	ft_putstr("Malloc error\n", 2);
	exit(1);
}

void	ft_error_command(char **envp, t_comm *command)
{
	int	index;

	index = -1;
	while (envp[++index])
		free(envp[index]);
	free(envp);
	ft_putstr("minishell: ", 2);
	ft_putstr(command->parameters[0], 2);
	ft_putstr(": command not found\n", 2);
	exit (127);
}
