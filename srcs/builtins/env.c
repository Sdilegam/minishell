/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:14:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/06 15:27:34 by sdi-lega         ###   ########.fr       */
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
		ft_printf("%s=%s\n", curr->var, curr->content);
		curr = curr->next;
	}
	g_status.status = 0;
}
