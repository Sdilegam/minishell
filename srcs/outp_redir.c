/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 16:14:34 by sdi-lega         ###   ########.fr       */
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
		if (file == -1)
		{
			ft_putstr("minishell: ", 2);
			ft_putstr(comm->next->parameters[0], 2);
			ft_putstr(": ", 2);
			perror("");
			exit(1);
		}
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
		if (file == -1)
		{
			ft_putstr("minishell: ", 2);
			ft_putstr(comm->next->parameters[0], 2);
			ft_putstr(": ", 2);
			perror("");
			exit(1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
		comm->previous->func(comm->previous, env);
		exit(0);
	}
	return (0);
}
