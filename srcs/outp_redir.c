/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/12 16:01:27 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outp_redir(t_comm *comm, t_env *env)
{
	int		file;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		file = open(comm->next->parameters[0], O_RDWR
				| O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		function(comm, env);
		exit(0);
	}
	return (0);
}

int	outp_redir_append(t_comm *comm, t_env *env)
{
	int		file;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		file = open(comm->next->parameters[0], O_RDWR
				| O_CREAT | O_APPEND, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		function(comm, env);
		exit(0);
	}
	return (0);
}
