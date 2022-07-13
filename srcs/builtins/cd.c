/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:44:52 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 14:17:32 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_replace(t_env *env)
{
	t_env	*curr;
	char	*content;

	curr = env;
	while (curr)
	{
		if (ft_strcmp("PWD", curr->var) == 0)
		{
			free(curr->content);
			curr->content = malloc(sizeof(char) * ft_strlen(getcwd(0, 0)) + 1);
			if (!curr->content)
			{
				free(curr->var);
				return (NULL);
			}
			content = getcwd(NULL, 0);
			curr->content = content;
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

t_env	*ft_cd(char **path, t_env *env)
{
	t_env	*new_env;

	if (ft_strcmp(path[1], "") == -1)
	{
		chdir(getenv("HOME"));
		g_status.status = 0;
	}
	if (chdir(path[1]) != 0)
	{
		g_status.status = 1;
		ft_putstr("cd: ", 2);
		ft_putstr(path[1], 2);
		ft_putstr(": ", 2);
		perror("");
		return (NULL);
	}
	new_env = find_replace(env);
	return (new_env);
}
