/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:30:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/15 15:31:50 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rd_line_here_doc(char *string, int fd_temp, int fd[2], char *temp)
{
	temp = readline(">");
	if (!temp)
	{
		g_status.status = 0 << 8;
		return (1);
	}
	while (ft_strcmp(string, temp) != 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_printf("%s\n", temp);
		free(temp);
		dup2(fd_temp, STDOUT_FILENO);
		temp = readline(">");
		if (!temp)
		{
			g_status.status = 0 << 8;
			return (1);
		}
	}
	close(fd[1]);
	close(fd_temp);
	free(temp);
	exit(g_status.status);
	return (0);
}

int	here_doc(t_comm *comm, t_env *env, int fd[2])
{
	char	*temp;
	char	*string;
	pid_t	id;
	int		fd_temp;

	(void)env;
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		signal(SIGINT, sig_exit);
		signal(SIGQUIT, SIG_IGN);
		fd_temp = dup(STDOUT_FILENO);
		string = comm->parameters[0];
		temp = NULL;
		if (rd_line_here_doc(string, fd_temp, fd, temp) == 1)
			exit (1);
		exit(0);
	}
	wait(NULL);
	return (0);
}

static void	pipe3(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		(void)env;
		signal(SIGQUIT, empty);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		comm->previous->func(comm->previous, env);
		wait(&g_status.status);
		exit(WEXITSTATUS(g_status.status));
	}
}

static void	pipe2(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		signal(SIGINT, empty);
		signal(SIGQUIT, empty);
		here_doc(comm, env, fd);
		wait(&g_status.status);
		exit(WEXITSTATUS(g_status.status));
	}
}

int	ft_delimiter_redir(t_comm *command, t_env *env)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (1);
	pipe2(fd, pid[0], command, env);
	g_status.status = -1;
	wait(0);
	if (g_status.status == 130 << 8)
	{
		g_status.status = 1 << 8;
		return (1);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		return (1);
	pipe3(fd, pid[1], command, env);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], &g_status.status, 0);
	return (0);
}
