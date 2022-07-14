/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:44:52 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 19:19:15 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_replace(t_env *env, t_comm *comm)
{
	t_env	*curr;
	char	*content;

	curr = env;
	while (curr)
	{
		if (ft_strcmp("PWD", curr->var) == 0)
		{
			free(curr->content);
			content = getcwd(NULL, 0);
			curr->content = content;
			if (!curr->content)
				ft_free_malloc_err(env, comm);
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

t_env	*ft_cd(char **path, t_env *env, t_comm *comm)
{
	t_env	*new_env;

	if (ft_strcmp(path[1], "") == -1 || ft_strcmp(path[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		g_status.status = 0 << 8;
	}
	else if (chdir(path[1]) != 0)
	{
		g_status.status = 1 << 8;
		ft_putstr("cd: ", 2);
		ft_putstr(path[1], 2);
		ft_putstr(": ", 2);
		perror("");
		return (NULL);
	}
	new_env = find_replace(env, comm);
	return (new_env);
}
