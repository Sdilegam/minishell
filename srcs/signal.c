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
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status.status = 1;
	}
	return ;
}

void	sig_handler_2(int sig)
{
	if (sig == SIGINT)
	{
		if (wait(NULL) != -1)
			ft_printf("\n");
		g_status.status = 130;
	}
	if (sig == SIGQUIT)
	{
		if (wait(NULL) != -1)
			ft_printf("Quit: 3\n");
		g_status.status = 131;
	}
	return ;
}

void	sig(void)
{
	signal(SIGINT, sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
