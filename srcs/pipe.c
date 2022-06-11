/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:44:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/11 17:02:57 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strcmp(str[i], "|") == 0)
			return (i);
	}
	return (0);
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

int	ft_pipe(t_comm *command, t_env *env)
{
	int		fd[2];
	pid_t	id;
	pid_t	id2;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		function(command, env);
		exit (0);
	}
	id2 = fork();
	if (id2 == -1)
		return (1);
	if (id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		function(command->next, env);
		exit(0);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
