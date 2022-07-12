/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:52:06 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/12 15:52:39 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir(t_comm *comm, t_env *env)
{
	int		file;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		file = open(comm->next->parameters[0], O_RDONLY);
		dup2(file, STDIN_FILENO);
		close(file);
		function(comm, env);
		exit(0);
	}
	return (0);
}
