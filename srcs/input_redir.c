/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:52:06 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 17:39:31 by abkasmi          ###   ########.fr       */
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
			write(2, "Bash: ", 7);
			ft_putstr(comm->next->parameters[1], 2);
			write(2, ": No such file or directory\n", 29);
			return (1);
		}
		dup2(file, STDIN_FILENO);
		close(file);
		comm->previous->func(comm->previous, env);
		exit(0);
	}
	return (0);
}
