/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:18:07 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/04 16:01:27 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comm	*initate_command(void)
{
	t_comm	*command;

	command = malloc(sizeof(t_comm));
	if (!command)
		return (0);
	command->func = 0;
	command->parameters = 0;
	command->next = 0;
	command->previous = 0;
	return (command);
}

t_comm	*create_command(char **parameters)
{
	t_comm	*command;

	command = initate_command();
	if (!command)
		return (0);
	command->parameters = parameters;
	return (command);
}

void	add_command(t_comm *first, t_comm *command)
{
	t_comm	*cursor;

	cursor = first;
	while (cursor->next)
	{
		cursor = cursor->next;
	}
	cursor->next = command;
	command->previous = cursor;
}
