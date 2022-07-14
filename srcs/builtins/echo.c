/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:59:47 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 15:23:43 by abkasmi          ###   ########.fr       */
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
	g_status.status = 0 << 8;
	return (0);
}
