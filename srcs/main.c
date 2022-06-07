/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/07 14:16:29 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

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
	{
		write(1, "exit\n", 5);
		exit(1);
	}
	else
	{
		if (fork() == 0)
			if (execve(command[0], command, envp) == -1)
				exit(1);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	char	*rl;
	char	**test;
	char	**env_str;
	int		result;
	t_env	*env;

	(void)ac;
	(void)av;
	print_header();
	env = set_env(envp);
	while (1)
	{
		sig();
		rl = readline("minishell:$>");
		if (!rl)
		{
			free(env);
			exit(1);
		}
		add_history(rl);
		test = read_line(rl);
		env_str = list_to_array(env);
		function(test, env, env_str);
		free(env_str);
		wait(&result);
	}
	rl_clear_history();
}
