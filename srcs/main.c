/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 12:56:12 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_commands(t_comm *command, t_env *env)
{
	if (ft_strcmp(command->parameters[0], "echo") == 0)
		ft_echo(command->parameters);
	else if (ft_strcmp(command->parameters[0], "cd") == 0)
		env = ft_cd(command->parameters, env);
	else if (ft_strcmp(command->parameters[0], "pwd") == 0)
	{
		ft_putstr(getcwd(NULL, 0), 1);
		ft_putstr("\n", 1);
	}
	else if (ft_strcmp(command->parameters[0], "env") == 0)
		ft_env(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "export") == 0)
		ft_export(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "unset") == 0)
		ft_unset(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "exit") == 0)
		ft_exit(command, env);
	else
		return (1);
	return (0);
}

void	exec(t_comm *command, t_env *env)
{
	char	**envp;
	int		index;

	index = -1;
	envp = list_to_array(env);
	if (execve(command->parameters[0], command->parameters, envp) == -1)
	{
		while (envp[++index])
			free(envp[index]);
		free(envp);
		ft_putstr("minishell: ", 2);
		ft_putstr(command->parameters[0], 2);
		perror(": ");
		if (errno != 2)
			exit(126);
		exit (127);
	}
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
			exec(command, env);
		}
		else
		{
			if (ft_strcmp(command->parameters[0], "./minishell") == 0
				|| ft_strcmp(command->parameters[0], "bash") == 0)
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

	if (ac != 1)
	{
		ft_printf("bash: %s: No such file or directory\n", av[1]);
		return (1);
	}
	print_header();
	init_var();
	env = set_env(envp);
	check_shlvl(env);
	while (1)
	{
		sig();
		header();
		rl = readline("minishell\033[0m$> ");
		check_rl(rl, env);
		comm = parse_parameters(rl, env);
		free(rl);
		sig2();
		comm_loop(comm, env);
	}
	ft_free_all(env, comm);
}
