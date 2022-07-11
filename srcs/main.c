/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/11 17:01:22 by sdi-lega         ###   ########.fr       */
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
		if (pid == 0)
		{	
			replace_comm(command, env);
			if (execve(command->parameters[0], command->parameters,
					list_to_array(env)) == -1)
			{
				ft_printf("minishell: %s: command not found\n", command->parameters[0]);
				// ft_printf("%d", errno);
				exit (127);
			}
		}
		else
		{
			if (ft_strcmp(command->parameters[0], "./minishell") == 0 || ft_strcmp(command->parameters[0], "bash") == 0)
			{
				signal(SIGQUIT, empty);
				signal(SIGINT, empty);
			}
			wait(&g_status.status);
		}
	}
	return (g_status.status);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*rl;  
	t_comm	*comm;
	t_env	*env;

	(void)ac;
	(void)av;
	print_header();
	g_status.status = 0;
	env = set_env(envp);
	while (1)
	{
		sig();
		// ft_printf("%d ", g_status.status);
		// ft_printf("%d\n", WEXITSTATUS(g_status.status));
		if (WEXITSTATUS(g_status.status) == 0 || WEXITSTATUS(g_status.status) == 130)
			ft_printf("\033[1;92m");
		else
			ft_printf("\033[1;91m");
		rl = readline("minishell\033[0m$> ");
		if (!rl)
		{
			free(env);
			exit(1);
		}
		add_history(rl);
		comm = parse_parameters(rl, env);
		signal(SIGINT, sig_handler_2);
		signal(SIGQUIT, sig_handler_2);
		if (comm)
			comm->func(comm, env);
		wait(NULL);
	}
	rl_clear_history();
}
