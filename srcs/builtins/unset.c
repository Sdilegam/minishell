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
	t_env	*temp;

	curr = env;
	i = 0;
	j = 0;
	while (str[++i])
	{
		if (ft_strcmp(str[i], curr->var) == 0)
		{
			free(curr->var);
			if (curr->content)
				free(curr->content);
			temp = curr->next;
			*curr = *temp;
			free(temp);
			continue ;
		}
		while (curr->next)
		{
			if (ft_strcmp(str[i], curr->next->var) == 0)
			{
				free(curr->next->var);
				if (curr->next->content)
					free(curr->next->content);
				temp = curr->next->next;
				free(curr->next);
				curr->next = temp;
				break ;
			}
			curr = curr->next;
		}
		curr = env;
	}
	return (0);
}
