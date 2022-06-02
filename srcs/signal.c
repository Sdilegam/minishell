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
 * le reecrire manuellement                      */

void	sig_handler(int sig)
{
	write(1, "\n", 1);
	write(1, "minishell:$>", 12);
	return ;
}

void	sig(void)
{
	signal(SIGINT, sig_handler);
	return ;
}