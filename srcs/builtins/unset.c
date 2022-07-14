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
	{
		g_status.status = 1 << 8;
		ft_putstr("unset: ", 2);
		ft_putstr(str, 2);
		ft_putstr(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[index])
	{
		if (!is_ok(str[index]) || str[index] == '=')
		{
			g_status.status = 1 << 8;
			ft_putstr("unset: ", 2);
			ft_putstr(str, 2);
			ft_putstr(": not a valid identifier\n", 2);
			return (1);
		}
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

int	ft_unset_loop(char **str, t_env *curr, t_env *env)
{
	int		i;
	t_env	*temp;

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

int	ft_unset(t_env *env, char **str)
{
	t_env	*curr;

	curr = env;
	if (ft_strcmp("PWD", str[1]) == 0)
	{
		g_status.status = 0 << 8;
		return (0);
	}
	if (ft_unset_loop(str, curr, env) == 1)
		return (1);
	g_status.status = 0 << 8;
	return (0);
}
