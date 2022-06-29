/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:14:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/29 13:34:55 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env, char **str)
{
	t_env	*curr;

	if (str[1])
	{
		ft_putstr("env: ");
		ft_putstr(str[1]);
		ft_putstr(": No such file or directory\n");
		g_status.status = 127;
		return ;
	}
	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->var, "?") != 0)
			ft_printf("%s=%s\n", curr->var, curr->content);
		curr = curr->next;
	}
	g_status.status = 0;
}
