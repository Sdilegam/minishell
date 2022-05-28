/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/28 02:43:13 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(char **command, t_env *env, char **envp)
{
	if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
	{
		ft_putstr(getcwd(NULL, 0));
		ft_putstr("\n");
	}
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(command[0], "export") == 0)
		ft_export(env, command);
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(env, command);
	else if (ft_strcmp(command[0], "exit") == 0)
		exit(0);
	else
	{
		if (fork() == 0)
			if (!execve(command[0], command, envp))
				exit(1);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	char	*rl;
	char	**test;
	int		result;
	t_env	*env;

	(void)ac;
	(void)av;
	print_header();
	env = set_env(envp);
	while (1)
	{
		rl = readline("minishell:$>");
		test = read_line(rl);
		function(test, env, envp);
		wait(&result);
	}
}
