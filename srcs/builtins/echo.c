/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:47 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 01:13:08 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **str)
{
	int	i;

	if (ft_strcmp(str[1], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			ft_printf(" ");
	}
	if (ft_strcmp(str[1], "-n"))
		ft_printf("\n");
	g_status.status = 0;
	return (0);
}
