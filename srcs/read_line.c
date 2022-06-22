// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   read_line.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/05/23 16:29:33 by sdi-lega          #+#    #+#             */
// /*   Updated: 2022/06/15 13:29:45 by sdi-lega         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// int	count_words(char *string)
// {
// 	int	count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while (string[i] && string[i] != '|')
// 	{
// 		if (!is_space(string[i]))
// 			count++;
// 		while (!is_space(string[i]) && string[i])
// 			i++;
// 		while (is_space(string[i]) && string[i])
// 			i++;
// 	}
// 	return (count);
// }

// char	*duplicate_word(char *string)
// {
// 	int		letters;
// 	int		index;
// 	char	*word;

// 	letters = 0;
// 	index = -1;
// 	while (!is_space(string[letters]) && string[letters])
// 			letters++;
// 	word = malloc(sizeof(char) * (letters + 1));
// 	while (++index < letters)
// 		word[index] = string[index];
// 	word[index] = 0;
// 	return (word);
// }

// char	**read_line(char *string)
// {
// 	int		i;
// 	int		count;
// 	char	**line;
// 	int		index;

// 	i = 0;
// 	index = -1;
// 	count = count_words(string);
// 	line = malloc((count + 1) * sizeof(char *));
// 	line[count] = 0;
// 	while (++index < count)
// 	{
// 		while (is_space(string[i]) && string[i])
// 			i++;
// 		line[index] = duplicate_word(string + i);
// 		while (!is_space(string[i]) && string[i])
// 			i++;
// 	}
// 	return (line);
// }

t_comm	*parse_parameters(char *string)
{
	t_comm	*command;
	t_comm	*cursor;
	int		i;

	command = create_command(read_line(string));
	if (!*(command->parameters))
		return (0);
	i = where_is_pipe(string);
	command->func = &function;
	cursor = command;
	while (i)
	{
		string += i + 1;
		cursor->func = &ft_pipe;
		add_command(command, create_command(read_line(string)));
		if (!*(cursor->next->parameters))
			return (0);
		cursor = cursor->next;
		cursor->func = &function;
		i = where_is_pipe(string);
	}
	return (command);
}
