/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:44:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/05 17:26:05 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	where_is_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += get_quote_len(str + i);
		if (str[i] == '|')
			return (i);
	}
	return (0);
}

static void	pipe2(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		function(comm, env);
		wait(NULL);
		exit (0);
	}
}

static void	pipe3(int fd[2], pid_t pid, t_comm *comm, t_env *env)
{
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		comm->next->func(comm->next, env);
		wait(NULL);
		exit(0);
	}
}

int	ft_pipe(t_comm *command, t_env *env)
{
	int		fd[2];
	pid_t	pid[2];

	signal(SIGQUIT, sig_handler_2);
	signal(SIGINT, SIG_IGN);
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
	// signal(SIGINT, sig_handler_2);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	// if (pid[0] == 0 || pid[1] == 0)
	// 	exit (0);
	return (0);
}
