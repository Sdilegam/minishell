/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:52:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 14:28:34 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_rl(char *rl, t_env *env)
{
	if (!rl)
	{
		ft_free_env(env);
		rl_clear_history();
		write(1, "exit\n", 6);
		exit(0);
	}
	add_history(rl);
}

void	comm_loop(t_comm *comm, t_env *env)
{
	if (comm)
	{
		sig2();
		g_status.status = -1;
		while (comm->next)
			comm = comm->next;
		comm->func(comm, env);
		while (comm->previous)
			comm = comm->previous;
	}
	ft_free_comm(comm);
	wait(NULL);
}

void	init_var(void)
{
	g_status.status = 0;
	g_status.file = -1;
}
