/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/26 10:17:28 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}				t_env;

t_env	*newnode(char *data);
t_env	*set_env(char **envp);

void	print_header(void);
void	ft_cd(char **path);
void	ft_putstr(char *str);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	print_env(t_env *env, int p);
void	insertnewnode(t_env *env, char *data);
void	ft_export(t_env *env, char **str);

int		is_space(char chara);
int		is_alpha(char chara);
int		count_words(char *string);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(char **str);

char	**read_line(char *string);

#endif
