/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/14 13:52:47 by sdi-lega         ###   ########.fr       */
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
	if (!command->parameters[0])
		exit (0);
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
			waitpid(pid, &g_status.status, 0);
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
	g_status.file = -1;
	env = set_env(envp);
	check_shlvl(env);
	while (1)
	{
		sig();
		// ft_printf("%d ", g_status.status);
		// ft_printf("%d\n", WEXITSTATUS(g_status.status));
		if (WEXITSTATUS(g_status.status) == 0
			|| WEXITSTATUS(g_status.status) == 130)
			ft_putstr("\033[1;92m", 2);
		else
			ft_printf("\033[1;91m", 2);
		rl = readline("minishell\033[0m$> ");
		if (!rl)
		{
			ft_free_env(env);
			rl_clear_history();
			exit(0);
		}
		add_history(rl);
		comm = parse_parameters(rl, env);
		free(rl);
		g_status.status = 0;
		signal(SIGINT, sig_handler_2);
		signal(SIGQUIT, sig_handler_2);
		if (comm)
		{
			while (comm->next)
				comm = comm->next;
			comm->func(comm, env);
			while (comm->previous)
				comm = comm->previous;
		}
		ft_free_comm(comm);
		wait(NULL);
	}
	ft_free_env(env);
	ft_free_comm(comm);
	rl_clear_history();
}
