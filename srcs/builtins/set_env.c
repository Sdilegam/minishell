/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:02:11 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 02:45:21 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cpy_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] != '=')
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		exit (1);
	i = -1;
	while (str[++i] != '=' && str[i])
		name[i] = str[i];
	name[i] = '\0';
	return (name);
}

char	*ft_cpy_content(char *str)
{
	char	*content;
	int		i;
	int		j;
	int		temp;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	i++;
	temp = i;
	while (str[i++])
		j++;
	content = malloc(sizeof(char) * j + 1);
	if (!content)
		exit (1);
	j = 0;
	while (str[temp])
		content[j++] = str[temp++];
	content[j] = '\0';
	return (content);
}

t_env	*newnode(char *data, char *data2)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->var = data;
	node->content = data2;
	node->next = NULL;
	return (node);
}

void	insertnewnode(t_env *env, char *data, char *data2)
{
	t_env	*node;
	t_env	*curr;

	node = newnode(data, data2);
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
	t_var	var;
	t_env	*env;

	i = 0;
	j = 0;
	if (!*envp)
		return (newnode(NULL, NULL));
	while (envp[j])
		j++;
	var.name = ft_cpy_name(envp[i]);
	var.content = ft_cpy_content(envp[i]);
	env = newnode(var.name, var.content);
	while (++i < j)
	{
		var.name = ft_cpy_name(envp[i]);
		var.content = ft_cpy_content(envp[i]);
		insertnewnode(env, var.name, var.content);
	}
	return (env);
}
