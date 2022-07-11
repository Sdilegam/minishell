/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:30:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/11 14:59:50 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_comm *comm, t_env *env)
{
	char	*temp;
	int		cmd;
	char	*string;

	string = comm->next->parameters[0];
	temp = readline(">");
	cmd = ft_strncmp(string, temp, ft_strlen(string));
	free(temp);
	if (cmd)
		here_doc(comm, env);
	function(comm, env);
	return (0);
}
