/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:36:12 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/28 02:36:12 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env *env, char **str)
{
	t_env	*curr;
	int		i;
	int		j;

	curr = env;
	i = 0;
	j = 0;
	while (str[++i])
	{
		while (curr->next)
		{
			if (ft_strcmp(str[i], curr->var) == 0)
			{
				env = env->next;
				free(curr->var);
				if (curr->content)
					free(curr->content);
				free(curr);
				break ;
			}
			env = env->next;
			curr = curr->next;
		}
		curr = env;
	}
	return (0);
}