/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:30:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/15 12:24:23 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *string)
{
	char	*temp;
	int		cmd;

	temp = readline(">");
	cmd = ft_strncmp(string, temp, ft_strlen(string));
	free(temp);
	if (cmd)
		here_doc(string);
}
