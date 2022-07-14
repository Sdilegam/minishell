/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:24:00 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/31 12:24:00 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_c(int sig)
{
	if (sig == SIGINT)
	{
		g_status.status = 130;
		write(1, "\n", 1);
		if (g_status.status == 0 || g_status.status == 130)
			ft_printf("\033[1;92m");
		else
			ft_printf("\033[1;91m");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	sig_handler_2(int sig)
{
	if (sig == SIGINT)
	{
		if (wait(NULL) != -1)
			ft_printf("\n");
	}
	if (sig == SIGQUIT)
	{
		if (wait(NULL) != -1)
		{
			ft_printf("Quit: 3\n");
		}
	}
	if (g_status.status >> 8 == -1)
		g_status.status = (128 + sig) << 8;
	return ;
}

void	sig_exit(int sig)
{
	if (sig == SIGINT)
	{
		g_status.status = 130 << 8;
		exit(g_status.status);
	}
}

void	sig(void)
{
	signal(SIGINT, sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	sig2(void)
{
	signal(SIGINT, sig_handler_2);
	signal(SIGQUIT, sig_handler_2);
	return ;
}
