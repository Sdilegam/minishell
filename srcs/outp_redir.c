/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 14:44:50 by sdi-lega         ###   ########.fr       */
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
		file = open(comm->parameters[0], O_RDWR
				| O_CREAT | O_TRUNC, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		comm->previous->func(comm->previous, env);
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
		file = open(comm->parameters[0], O_RDWR
				| O_CREAT | O_APPEND, 0777);
		dup2(file, STDOUT_FILENO);
		close(file);
		comm->previous->func(comm->previous, env);
		exit(0);
	}
	return (0);
}
