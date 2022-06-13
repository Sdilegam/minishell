/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/06/13 13:30:41 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"
/* 
# include <readline/readline.h>
# include <readline/history.h>
*/
# define READLINE_LIBRARY
# include <stdio.h>
# include "readline.h"
# include "history.h"

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

# include "type_definitions.h"

t_env	*newnode(char *data, char *data2);
t_env	*set_env(char **envp);

t_comm	*create_command(char **parameters);
t_comm	*parse_parameters(char *string);

void	print_header(void);
void	ft_cd(char **path);
void	ft_putstr(char *str);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	print_env(t_env *env, int p);
void	insertnewnode(t_env *env, char *data, char *data2);
void	ft_export(t_env *env, char **str);
void	ft_name_varr(t_env *env);
void	free_list(t_env *pHead);
void	sig(void);
void	sig_handler_c(int sig);
void	sig_handler_backslash(int sig);
void	add_command(t_comm *first, t_comm *command);

int		is_space(char chara);
int		is_alpha(char chara);
int		count_words(char *string);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(char **str);
int		ft_unset(t_env *env, char **str);
int		ft_strlen(char *str);
int		is_ok(char chara);
int		export_error(char *str);
int		unset_error(char *str);
int		ft_pipe(t_comm *command, t_env *env, int n_pipe);
int		is_pipe(char *str);
int		function(t_comm *command, t_env *env, int n);
int		where_is_pipe(char *str);



char	**read_line(char *string);
char	*ft_cpy_content(char *str);
char	*ft_cpy_name(char *str);

char	**list_to_array(t_env *list);
#endif
