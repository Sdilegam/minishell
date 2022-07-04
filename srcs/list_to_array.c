/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:44:16 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/15 12:21:12 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_node(t_env node)
{
	int		length;
	int		index;
	char	*string;

	index = -1;
	if (!node.var)
		return (0);
	length = ft_strlen(node.content) + ft_strlen(node.var);
	string = malloc((length + 2) * sizeof(char));
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

char	**list_to_array(t_env *list)
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
	iterator = list;
	index = -1;
	while (iterator)
	{
		env[++index] = copy_node(*iterator);
		iterator = iterator->next;
	}
	env[++index] = 0;
	return (env);
}
