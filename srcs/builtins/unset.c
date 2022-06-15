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

int	unset_error(char *str)
{
	int	index;

	index = 0;
	if (('0' <= str[0] && str[0] <= '9') || str[index] == '=')
		return (ft_printf("unset : %s: not a valid identifier\n", str));
	while (str[index])
	{
		if (!is_ok(str[index]) || str[index] == '=')
			return (ft_printf("unset : %s: not a valid identifier\n", str));
		index++;
	}
	return (0);
}

void	unset2(char **str, t_env *env, int i)
{
	t_env	*temp;
	t_env	*curr;

	curr = env;
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
}

int	ft_unset(t_env *env, char **str)
{
	t_env	*curr;
	int		i;
	t_env	*temp;

	curr = env;
	i = 0;
	while (str[++i])
	{
		if (unset_error(str[i]))
			return (1);
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
		unset2(str, env, i);
		curr = env;
	}
	return (0);
}
