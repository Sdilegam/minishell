/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/23 11:22:05 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outp_redir(t_comm *comm, t_env *env)
{
	int		fd[2];
	pid_t	id[2];

	id[0] = fork();
	if (id[0] == -1)
		return (1);
	if (id[0] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		close(fd[1]);
		function(comm, env);
	}
	id[1] = fork();
	if (id[1] == -1)
		return (1);
	if (id[1] == 0)
	{
		close(fd[1]);
		// if (>>)
		// 	dup2(fd[0], open(comm->parameters[1], O_CREAT | O_RDWR | O_APPEND));
		// else
			dup2(fd[0], open(comm->parameters[1], O_CREAT | O_RDWR));
		//ft_putstr_fd(fd[0], comm->parameters[])
		close(fd[0]);
	}
	return (0);
}
