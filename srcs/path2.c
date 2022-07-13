/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:31:33 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 18:32:13 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *source, int len)
{
	int		index;
	char	*copy;

	if (!source)
		return (NULL);
	index = -1;
	copy = calloc(len, sizeof(char));
	while (++index != len)
	{
		copy[index] = source[index];
	}
	return (copy);
}

void	change_comm(char *path, t_comm *comm)
{
	char	*temp;
	int		path_len;
	int		comm_len;
	int		index;

	index = -1;
	path_len = ft_strlen(path);
	comm_len = ft_strlen(comm->parameters[0]);
	temp = calloc (path_len + 1 + comm_len + 1, sizeof(char));
	while (path[++index])
		temp [index] = path[index];
	temp [index] = '/';
	while (comm->parameters[0][++index - 1 - path_len])
	{
		temp [index] = comm->parameters[0][index - 1 - path_len];
	}
	free (comm->parameters[0]);
	comm->parameters[0] = temp;
}
