/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:12:25 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/28 16:24:09 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_comm *comm)
{
// 	int	i;

// 	i = -1;
	if (comm->parameters[1])
	{
		write(1, "exit\n", 6);
		ft_printf("export : %s: numeric argument required\n",
			comm->parameters[1]);
		g_status = 255;
		exit(g_status);
	}
	else
	{
		write(1, "exit\n", 6);
		g_status = 0;
		exit(g_status);
	}
}