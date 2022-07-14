/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 14:27:06 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe3(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		(void)env;
		signal(SIGQUIT, empty);
		close(fd[0]);
		close(fd[1]);
		dup2(g_status.file, STDOUT_FILENO);
		comm->previous->func(comm->previous, env);
		close(g_status.file);
		wait(&g_status.status);
		exit(WEXITSTATUS(g_status.status));
	}
}

static void	pipe2(int fd[2], pid_t pid, t_comm *comm)
{
	if (pid == 0)
	{
		(void)comm;
		signal(SIGINT, empty);
		signal(SIGQUIT, empty);
		dup2(fd[0], g_status.file);
		close(fd[0]);
		wait(&g_status.status);
		exit(WEXITSTATUS(g_status.status));
	}
}

static void	open_file(t_comm *comm)
{
	g_status.file = open(comm->parameters[0], O_RDWR
			| O_CREAT | O_TRUNC, 0777);
	if (g_status.file == -1)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(comm->next->parameters[0], 2);
		ft_putstr(": ", 2);
		perror("");
		exit(1);
	}
}

int	ft_output_redir(t_comm *comm, t_env *env)
{
	pid_t	pid[2];
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	open_file(comm);
	pid[0] = fork();
	if (pid[0] == -1)
		return (1);
	pipe2(fd, pid[0], comm);
	g_status.status = 0;
	wait(0);
	if (g_status.status == 130 << 8)
		return (1);
	pid[1] = fork();
	if (pid[1] == -1)
		return (1);
	pipe3(fd, pid[1], comm, env);
	close(fd[1]);
	close(fd[0]);
	close(g_status.file);
	g_status.file = -1;
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], &g_status.status, 0);
	return (0);
}
