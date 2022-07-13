/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 15:10:09 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include "type_definitions.h"

t_env	*newnode(char *data, char *data2);
t_env	*set_env(char **envp);

t_comm	*create_command(char **parameters);
t_comm	*parse_parameters(char *string, t_env *env);

void	print_header(void);
t_env	*ft_cd(char **path, t_env *env);
void	ft_putstr(char *str, int fd);
void	ft_pwd(void);
void	ft_env(t_env *env, char **str);
void	print_env(t_env *env, int p);
void	insertnewnode(t_env *env, char *data, char *data2);
void	ft_export(t_env *env, char **str);
void	ft_name_varr(t_env *env);
void	free_list(t_env *pHead);
void	sig(void);
void	sig_handler_c(int sig);
void	sig_handler_backslash(int sig);
void	add_command(t_comm *first, t_comm *command);
void	ft_exit(t_comm *comm);
void	sig_handler_2(int sig);
char	*ft_itoa(int n);
void	sig_exit(int sig);
int		ft_atoi(const char *str);
int		check_shlvl(t_env *env);

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
int		ft_pipe(t_comm *command, t_env *env);
int		is_pipe(char *str);
int		function(t_comm *command, t_env *env);
int		where_is_pipe(char *str);
int		outp_redir_append(t_comm *comm, t_env *env);
int		input_redir(t_comm *comm, t_env *env);
int		input_delimiter(t_comm *comm, t_env *env);
int		ft_delimiter_redir(t_comm *command, t_env *env);

int		get_quote_len(char *string);
char	**read_line(char *string);
int		builtins_commands(t_comm *command, t_env *env);

char	*ft_cpy_content(char *str);
char	*ft_cpy_name(char *str);

int		count_quotes(char *string, int len);
t_env	*search_variable(t_env *env, char *string, int len);
void	duplicate_quotes(char *str_to, char *str_from);
int		get_final_len(char *string, t_env *env, int len);
int		ft_strncmp(char *s1, char *s2, int len);
int		duplicate_var(char *str_to, char *str_from, t_env *env);
char	**list_to_array(t_env *list);
char	*replace_dollars(char *base_str, t_env *env, int len);
int		get_variable_len(t_env var);
void	replace_comm(t_comm *comm, t_env *env);
int		is_p_redi(char *c);
void	empty(int sig);
int		outp_redir(t_comm *comm, t_env *env);
int		here_doc(t_comm *comm, t_env *env, int fd[2]);
#endif
