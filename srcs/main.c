/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/13 13:39:09 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	function(t_comm *command, t_env *env, int n)
{
	(void)n;
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
		ft_env(env);
	else if (ft_strcmp(command->parameters[0], "export") == 0)
		ft_export(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "unset") == 0)
		ft_unset(env, command->parameters);
	else if (ft_strcmp(command->parameters[0], "exit") == 0)
	{
		write(1, "exit\n", 5);
		exit(1);
	}
	else
	{
		if (fork() == 0)
			if (execve(command->parameters[0], command->parameters,
					list_to_array(env)) == -1)
				exit(1);
	}
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*rl;
	int		result;
	int		n_pipe;
	t_comm	*comm;
	t_env	*env;

	(void)ac;
	(void)av;
	print_header();
	env = set_env(envp);
	sig();
	while (1)
	{
		rl = readline("minishell:$>");
		if (!rl)
		{
			free(env);
			exit(1);
		}
		add_history(rl);
		n_pipe = is_pipe(rl);
		comm = parse_parameters(rl);
		comm->func(comm, env, n_pipe);
		wait(&result);
	}
	rl_clear_history();
}
