/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 02:28:33 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/14 17:14:00 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

int	get_path_len(char *path)
{
	int	len;

	len = -1;
	while (path [++len] && path[len] != ':')
	{
	}	
	return (len);
}

int	parse_dir(DIR *dir, char *path, t_comm *comm, t_env *env)
{
	struct dirent	*directory;

	if (dir)
	{
		directory = readdir(dir);
		while (directory)
		{
			if (ft_strcmp(comm->parameters[0], directory->d_name) == 0)
			{
				change_comm(path, comm, env);
				closedir(dir);
				return (0);
			}
			directory = readdir(dir);
		}
	}
	return (1);
}

void	parse_path(t_comm *comm, char *path, t_env *env)
{
	char	*dirpath;
	int		len;
	DIR		*file_des;

	while (*path)
	{
		len = get_path_len(path);
		dirpath = ft_strncpy(path, len, env, comm);
		if (dirpath)
		{
			file_des = opendir(dirpath);
			if (parse_dir(file_des, dirpath, comm, env) == 1)
			{
				path += len;
				if (*path)
					path += 1;
			}
			else
				break ;
			if (file_des)
				closedir(file_des);
			free(dirpath);
		}
	}
}

int	check_builtins(char *comm)
{
	if (ft_strcmp(comm, "echo") == 0 \
	|| ft_strcmp(comm, "cd") == 0 \
	|| ft_strcmp(comm, "pwd") == 0 \
	|| ft_strcmp(comm, "env") == 0 \
	|| ft_strcmp(comm, "export") == 0 \
	|| ft_strcmp(comm, "unset") == 0 \
	|| ft_strcmp(comm, "exit") == 0)
		return (1);
	return (0);
}

void	replace_comm(t_comm *comm, t_env *env)
{
	t_env	*path;

	if (check_builtins(comm->parameters[0]) == 0)
	{
		path = search_variable(env, "PATH", 4);
		if (!path)
			return ;
		parse_path(comm, path->content, env);
	}
}
