/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:44:43 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/13 14:25:05 by abkasmi          ###   ########.fr       */
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

int	ft_pipe(t_comm *command, t_env *env, int n_pipe)
{
	int		fd[2];
	int		p;
	pid_t	id;
	pid_t	id2;
	t_comm	*curr;

	curr = command;
	p = 0;
	while (curr && p < n_pipe)
	{
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
			function(curr, env, p);
			exit (0);
		}
		id2 = fork();
		if (id2 == -1)
			return (1);
		if (id2 == 0)
		{
			if (p == n_pipe - 1)
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}
			else
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			function(curr->next, env, p);
			exit(0);
		}
		curr = curr->next;
		p++;
		close(fd[1]);
		close(fd[0]);
		waitpid(id, NULL, 0);
		waitpid(id2, NULL, 0);
	}
	return (0);
}
