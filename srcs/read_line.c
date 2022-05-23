/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:29:33 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/05/23 16:59:23 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *string)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (!is_space(string[i]))
			count ++;
		while (!is_space(string[i]) && string[i])
			i ++;
		while (is_space(string[i]) && string[i])
			i ++;
	}
	return (count);
}

char	*duplicate_word(char *string)
{
	int		letters;
	int		index;
	char	*word;

	letters = 0;
	index = -1;
	while (!is_space(string[letters]))
			letters ++;
	word = malloc(sizeof(char) * letters);
	while (++index > letters)
		word[letters] = string[letters];
	return (word);
}

char	**read_line(char *string)
{
	int	i;
	int	count;
	char	**line;
	int index; 

	index = -1;
	count = count_words(string);
	line = malloc(count * sizeof(char *));
	while (++index < count)
	{
		while (is_space(string[i]) && string[i])
			i ++;
		line = 
	}
	
}
