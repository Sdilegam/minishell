/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/23 20:31:01 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(char **command)
{
	if (fork() == 0)
		if (!execve(command[0], command, command))
			exit(1);
}

int	main(void)
{
	char	*rl;
	char	**test;
	int		result;

	print_header();
	while (1)
	{
		rl = readline("minishell:$>");
		test = read_line(rl);
		function(test);
		wait(&result);
	}
}
