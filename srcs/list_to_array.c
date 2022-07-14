/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:44:16 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/14 17:09:23 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_node(t_env node, t_env *env, t_comm *comm)
{
	int		length;
	int		index;
	char	*string;

	index = -1;
	if (!node.var)
		return (0);
	length = ft_strlen(node.content) + ft_strlen(node.var);
	string = malloc((length + 2) * sizeof(char));
	if (!string)
		ft_free_malloc_err(env, comm);
	length = -1;
	while (node.var[++index])
		string[++length] = node.var[index];
	index = -1;
	string[++length] = '=';
	while (node.content[++index])
		string[++length] = node.content[index];
	string[++length] = 0;
	return (string);
}

char	**list_to_array(t_env *list, t_comm *comm)
{
	int		index;
	t_env	*iterator;
	char	**env;

	iterator = list;
	index = 0;
	while (iterator)
	{
		index ++;
		iterator = iterator->next;
	}
	env = malloc((index + 1) * sizeof(char *));
	if (!env)
		ft_free_malloc_err(list, comm);
	iterator = list;
	index = -1;
	while (iterator)
	{
		env[++index] = copy_node(*iterator, list, comm);
		iterator = iterator->next;
	}
	env[++index] = 0;
	return (env);
}
