/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:52:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 19:17:58 by sdi-lega         ###   ########.fr       */
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

void	check_rl(char *rl, t_env *env)
{
	if (!rl)
	{
		ft_free_env(env);
		rl_clear_history();
		system("leaks minishell");
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
