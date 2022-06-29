/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/29 14:49:03 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_commands(t_comm *command, t_env *env)
{
	if (ft_strcmp(command->parameters[0], "echo") == 0)
		ft_echo(command->parameters);
	else if (ft_strcmp(command->parameters[0], "cd") == 0)
		ft_cd(command->parameters);
	else if (ft_strcmp(command->parameters[0], "pwd") == 0)
	{
		ft_putstr(getcwd(NULL, 0));
		ft_putstr("\n");
	}
	else if (ft_strcmp(command->parameters[0], "env") == 0)
		ft_env(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "export") == 0)
		ft_export(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "unset") == 0)
		ft_unset(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "exit") == 0)
		ft_exit(command);
	else
		return (1);
	return (0);
}

int	function(t_comm *command, t_env *env)
{
	pid_t	pid;

	if (builtins_commands(command, env) == 1)
	{
		pid = fork();
		g_status.pid = pid;
		signal(SIGINT, sig_handler_2);
		signal(SIGQUIT, sig_handler_2);
		if (pid == 0)
		{
			if (execve(command->parameters[0], command->parameters,
					list_to_array(env)) == -1)
				exit(1);
		}
		else
			wait(NULL);
	}
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*rl;
	t_comm	*comm;
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
		// ft_printf("Number of words: %d.\n", count_words(rl));
		add_history(rl);
		comm = parse_parameters(rl, env);
		if (comm)
			comm->func(comm, env);
		free (rl);
	}
	rl_clear_history();
}
