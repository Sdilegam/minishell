/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/15 13:31:13 by sdi-lega         ###   ########.fr       */
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
t_env	*ft_cd(char **path, t_env *env, t_comm *comm);
void	ft_putstr(char *str, int fd);
void	ft_pwd(void);
void	ft_env(t_env *env, char **str);
void	print_env(t_env *env, int p);
void	insertnewnode(t_env *env, char *data, char *data2);
void	ft_export(t_env *env, char **str);
void	sig(void);
void	sig_handler_c(int sig);
void	add_command(t_comm *first, t_comm *command);
void	ft_exit(t_comm *comm, t_env *env);
void	sig_handler_2(int sig);
char	*ft_itoa(int n);
void	sig_exit(int sig);
int		ft_atoi(const char *str);
int		check_shlvl(t_env *env);
int		ft_output_redir(t_comm *comm, t_env *env);
int		ft_output_redir_append(t_comm *comm, t_env *env);
char	*ft_strncpy(char *source, int len, t_env *env, t_comm *comm);
void	change_comm(char *path, t_comm *comm, t_env *env);
void	ft_free_malloc_err(t_env *env, t_comm *comm);

int		is_space(char chara);
int		count_words(char *string, int *quotes);
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
int		count_p_redi(char *string);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_all(t_env *env, t_comm *comm);
void	comm_loop(t_comm *comm, t_env *env);
void	check_rl(char *rl, t_env *env);
void	sig2(void);
void	init_var(void);
int		len_int(int n);
int		get_quote_len(char *string);
char	**read_line(char *string, t_env *env, t_comm *comm);
int		builtins_commands(t_comm *command, t_env *env);

char	*ft_cpy_content(char *str);
char	*ft_cpy_name(char *str);
int		get_redi_len(char *string);
void	parse_new_coms(char *string, int i, t_comm *first_com, t_env *env);
t_comm	*parse_parameters(char *string, t_env *env);
int		check_string(char *string);
int		not_allowed_char(char chara);
int		check_quotes(char *string);
int		err_redi(char *string, int offset, int which_redi);
int		check_redi(char *string, int index);
int		get_offset(char *string, int index);
int		check_pipe(char *string, int index);
int		(*set_comm(char *chara))(t_comm *comm, t_env *env);
void	ft_pwd(void);
void	ft_error_command(char **envp, t_comm *command);

int		count_quotes(char *string, int len);
t_env	*search_variable(t_env *env, char *string, int len);
void	duplicate_quotes(char *str_to, char *str_from);
int		get_final_len(char *string, t_env *env, int len);
int		ft_strncmp(char *s1, char *s2, int len);
int		duplicate_var(char *str_to, char *str_from, t_env *env);
char	**list_to_array(t_env *list, t_comm *comm);
char	*replace_dollars(char *base_str, t_env *env, int len, t_comm *comm);
int		get_variable_len(t_env var);
void	replace_comm(t_comm *comm, t_env *env);
int		is_p_redi(char *c);
void	empty(int sig);
int		outp_redir(t_comm *comm, t_env *env);
int		here_doc(t_comm *comm, t_env *env, int fd[2]);
void	ft_free_comm(t_comm *comm);
void	ft_free_env(t_env *env);
int		check_string(char *string);
int		var_id_len(char *string);

#endif
