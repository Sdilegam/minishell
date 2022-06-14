/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:44:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/14 06:05:42 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			count++;
	}
	return (count);
}

int	where_is_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (i);
	return (0);
}

// int	ft_pipe(t_comm *command, t_env *env)
// {
// 	int		fd[2];
// 	pid_t	id;
// 	pid_t	id2;

// 	if (pipe(fd) == -1)
// 		return (1);
// 	id = fork();
// 	if (id == -1)
// 		return (1);
// 	if (id == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		function(command, env);
// 		exit (0);
// 	}
// 	waitpid(id, NULL, 0);
// 	id2 = fork();
// 	if (id2 == -1)
// 		return (1);
// 	if (id2 == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		command->next->func(command->next, env);
// 		exit(0);
// 	}
// 	close(fd[1]);
// 	close(fd[0]);
// 	waitpid(id2, NULL, 0);
// 	return (0);
// }

int	ft_pipe(t_comm *command, t_env *env)
{
	int	def[2];
	int	fd[2];

	def[0] = dup(STDIN_FILENO);
	def[1] = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	function(command, env);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(def[1], STDOUT_FILENO);
	command->next->func(command->next, env);
	dup2(def[0], STDIN_FILENO);
	return (0);
}
