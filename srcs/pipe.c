/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:44:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 01:51:18 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty(int sig)
{
	(void)sig;
	return ;
}

int	where_is_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += get_quote_len(str + i);
		if (is_p_redi(str + i) != 0)
			return (i);
	}
	return (ft_strlen(str));
}

static void	pipe2(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		signal(SIGINT, empty);
		signal(SIGQUIT, empty);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (comm->previous->func(comm->previous, env) == 1)
			exit (1);
		wait(&g_status.status);
		exit (WEXITSTATUS(g_status.status));
	}
}

static void	pipe3(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		signal(SIGINT, empty);
		signal(SIGQUIT, empty);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		function(comm, env);
		wait(&g_status.status);
		exit(WEXITSTATUS(g_status.status));
	}
}

int	ft_pipe(t_comm *command, t_env *env)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (1);
	pipe2(fd, pid[0], command, env);
	pid[1] = fork();
	if (pid[1] == -1)
		return (1);
	pipe3(fd, pid[1], command, env);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid[1], &g_status.status, 0);
	waitpid(pid[0], 0, 0);
	return (0);
}
