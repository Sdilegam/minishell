/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:02:11 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/25 14:05:14 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*newnode(char *data)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->var = data;
	node->next = NULL;
	return (node);
}

void	insertnewnode(t_env *env, char *data)
{
	t_env	*node;
	t_env	*curr;

	node = newnode(data);
	if (env == NULL)
		env = node;
	else
	{
		curr = env;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

t_env	*set_env(char **envp)
{
	int		i;
	int		j;
	t_env	*env;

	i = 0;
	j = 0;
	while (envp[j])
		j++;
	env = newnode(envp[i]);
	while (++i < j)
		insertnewnode(env, envp[i]);
	return (env);
}
