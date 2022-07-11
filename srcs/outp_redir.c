/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outp_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:48:08 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/11 14:33:07 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outp_redir(t_comm *comm, t_env *env)
{
	(void)comm;
	(void)env;
	ft_printf("output redirection\n");
	// int		fd[2];
	// pid_t	id[2];

	// id[0] = fork();
	// if (id[0] == -1)
	// 	return (1);
	// if (id[0] == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDIN_FILENO);
	// 	close(fd[1]);
	// 	function(comm, env);
	// }
	// id[1] = fork();
	// if (id[1] == -1)
	// 	return (1);
	// if (id[1] == 0)
	// {
	// 	close(fd[1]);
	// 	// if (>>)
	// 	// 	dup2(fd[0], open(comm->parameters[1], O_CREAT | O_RDWR | O_APPEND));
	// 	// else
	// 		dup2(fd[0], open(comm->parameters[1], O_CREAT | O_RDWR));
	// 	//ft_putstr_fd(fd[0], comm->parameters[])
	// 	close(fd[0]);
	// }
	return (0);
}
