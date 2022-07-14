/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:52:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 15:03:09 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	if (WEXITSTATUS(g_status.status) == 0
		|| WEXITSTATUS(g_status.status) == 130)
		ft_printf("\033[1;92m");
	else
		ft_printf("\033[1;91m");
}
	// ft_printf("%d ", g_status.status);
	// ft_printf("%d\n", WEXITSTATUS(g_status.status));

void	check_rl(char *rl, t_env *env)
{
	if (!rl)
	{
		ft_free_env(env);
		rl_clear_history();
		exit(0);
	}
	add_history(rl);
}

void	comm_loop(t_comm *comm, t_env *env)
{
	g_status.status = 0;
	sig2();
	if (comm)
	{
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
