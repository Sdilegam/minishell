/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:12:25 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 11:45:38 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

void	digit_err(t_comm *comm, t_env *env)
{
	write(1, "exit\n", 6);
	ft_putstr("exit: ", 2);
	ft_putstr(comm->parameters[1], 2);
	ft_putstr(": numeric argument required\n", 2);
	ft_free_comm(comm);
	ft_free_env(env);
	rl_clear_history();
	g_status.status = 255;
	exit(g_status.status);
}

void	ft_exit(t_comm *comm, t_env *env)
{
	int	i;

	i = -1;
	while (ft_isdigit(comm->parameters[1][++i]))
		;
	if (!ft_isdigit(comm->parameters[1][i])
		&& i != ft_strlen(comm->parameters[1]))
		digit_err(comm, env);
	else if (ft_atoi(comm->parameters[1]) && ft_arrlen(comm->parameters) > 2)
	{
		ft_free_comm(comm);
		ft_free_env(env);
		rl_clear_history();
		write(1, "exit\n", 6);
		ft_putstr("bash: exit: too many arguments\n", 2);
		g_status.status = 1;
		exit(g_status.status);
	}
	ft_free_comm(comm);
	ft_free_env(env);
	rl_clear_history();
	write(1, "exit\n", 6);
	exit(ft_atoi(comm->parameters[1]) % 255);
}
