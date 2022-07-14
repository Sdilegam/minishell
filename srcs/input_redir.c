/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:52:06 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 19:18:04 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir(t_comm *comm, t_env *env)
{
	int		file;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		file = open(comm->parameters[0], O_RDONLY);
		if (file == -1)
		{
			g_status.status = 1 << 8;
			write(2, "Bash: ", 7);
			ft_putstr(comm->parameters[1], 2);
			write(2, ": No such file or directory\n", 29);
			return (1);
		}
		dup2(file, STDIN_FILENO);
		close(file);
		comm->previous->func(comm->previous, env);
		exit(0);
	}
	wait(&g_status.status);
	return (0);
}
