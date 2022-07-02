/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 02:28:33 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/07/02 03:25:28 by sdi-lega         ###   ########.fr       */
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

char	*ft_strncpy(char *source, int len)
{
	int		index;
	char	*copy;

	index = -1;
	copy = calloc(len, sizeof(char));
	while (++index != len)
	{
		copy[index] = source[index];
	}
	return (copy);
}

void	change_comm(char *path, t_comm *comm)
{
	char	*temp;
	int		path_len;
	int		comm_len;
	int		index;

	index = -1;
	path_len = ft_strlen(path);
	comm_len = ft_strlen(comm->parameters[0]);
	temp = calloc (path_len + 1 + comm_len + 1, sizeof(char));
	while (path[++index])
		temp [index] = path[index];
	temp [index] = '/';
	while (comm->parameters[0][++index - 1 - path_len])
	{
		temp [index] = comm->parameters[0][index - 1 - path_len];
	}
	free (comm->parameters[0]);
	comm->parameters[0] = temp;
}

int	parse_dir(DIR *dir, char *path, t_comm *comm)
{
	struct dirent	*directory;

	if (dir)
	{
		directory = readdir(dir);
		while (directory)
		{
			if (ft_strcmp(comm->parameters[0], directory->d_name) == 0)
			{
				change_comm(path, comm);
				closedir(dir);
				return (0);
			}
			directory = readdir(dir);
		}
	}
	return (1);
}

void	parse_path(t_comm *comm, char *path)
{
	char	*dirpath;
	int		len;
	DIR		*file_des;

	while (*path)
	{
		len = get_path_len(path);
		dirpath = ft_strncpy(path, len);
		if (dirpath)
		{
			file_des = opendir(dirpath);
			if (parse_dir(file_des, dirpath, comm) == 0)
				return ;
		}
		path += len + 1;
		closedir(file_des);
	}
}

void	replace_comm(t_comm *comm, t_env *env)
{
	char			*path;

	path = search_variable(env, "PATH", 4)->content;
	parse_path(comm, path);
}