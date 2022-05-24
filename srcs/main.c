/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/24 14:59:15 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0));
	else
	{
		if (fork() == 0)
			if (!execve(command[0], command, command))
				exit(1);
	}
}

int	main(int ac, char *av[], char *envp[])
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
