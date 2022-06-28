/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:44:52 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/21 11:35:58 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **path)
{
	if (ft_strcmp(path[1], "") == -1)
	{
		chdir(getenv("HOME"));
		g_status = 0;
		return ;
	}
	if (chdir(path[1]) != 0)
	{
		g_status = 1;
		ft_putstr("cd: ");
		ft_putstr(path[1]);
		ft_putstr(": ");
		perror("");
	}
}
