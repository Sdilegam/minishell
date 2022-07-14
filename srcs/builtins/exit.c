/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:12:25 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 10:43:07 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_comm *comm, t_env *env)
{
	if (comm->parameters[1])
	{
		system("leaks minishell");
		ft_free_comm(comm);
		ft_free_env(env);
		rl_clear_history();
		write(1, "exit\n", 6);
		ft_putstr("exit: ", 2);
		ft_putstr(comm->parameters[1], 2);
		ft_putstr(": numeric argument required\n", 2);
		g_status.status = 2;
		exit(g_status.status);
	}
	else
	{
		system("leaks minishell");
		ft_free_comm(comm);
		ft_free_env(env);
		rl_clear_history();
		write(1, "exit\n", 6);
		g_status.status = 0;
		exit(g_status.status);
	}
}
