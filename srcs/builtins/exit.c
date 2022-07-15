/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:12:25 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 15:04:51 by sdi-lega         ###   ########.fr       */
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
	ft_putstr("exit: ", 2);
	ft_putstr(comm->parameters[1], 2);
	ft_putstr(": numeric argument required\n", 2);
	ft_free_comm(comm);
	ft_free_env(env);
	rl_clear_history();
	exit(255);
}

void	ft_exit(t_comm *co, t_env *env)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	write(1, "exit\n", 6);
	if (ft_arrlen(co->parameters) > 1)
	{
		while (ft_isdigit(co->parameters[1][++i]))
			;
		if (!ft_isdigit(co->parameters[1][i])
			&& i != ft_strlen(co->parameters[1]))
			digit_err(co, env);
		else if (ft_atoi(co->parameters[1]) && ft_arrlen(co->parameters) > 2)
		{
			ft_putstr("bash: exit: too many arguments\n", 2);
			ret = 1;
		}
	}
	if (ret == 0 && co->parameters[1])
		ret = ft_atoi(co->parameters[1]) % 255;
	ft_free_comm(co);
	ft_free_env(env);
	rl_clear_history();
	exit(ret);
}
