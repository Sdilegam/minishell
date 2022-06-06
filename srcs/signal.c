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

/*************************************************\
 * Ne fonctionne pas correctement quand on lance *
 * minishell dans minishell il faut surement     *
 * trouver un moyen de remttre le prompte sans   *
 * le reecrire manuellement                      *
 * ***********************************************/

void	sig_handler_c(int sig)
{
	// rl_replace_line("", 0);
	// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_redisplay();
	write(1, "salut", 5);
	return ;
}

void	sig_handler_backslash(int sig)
{
	int	a;

	a = 1;
	a++;
	return ;
}

void	sig(void)
{
	int	eof;

	eof = getc;
	if (signal(SIGINT, sig_handler_c) == SIG_ERR)
		exit (1);
	signal(SIGQUIT, sig_handler_backslash);
	return ;
}
