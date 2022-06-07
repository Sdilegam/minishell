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
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sig_handler_backslash(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	sig(void)
{
	signal(SIGINT, sig_handler_c);
	signal(SIGQUIT, sig_handler_backslash);
	return ;
}
