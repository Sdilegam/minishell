/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:14:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/25 15:09:28 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env, char **str)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = env;
	while (str[1][i])
	{
		if (str[1][i] == '=')
			break ;
		//write(1, "ici\n", 4);
		i++;
	}
	if (str[1][i] != '=')
	{
		ft_putstr("env: ");
		ft_putstr(str[2]);
		ft_putstr(": ");
		perror("");
		return ;
	}
	while (curr)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
}
