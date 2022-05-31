/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/31 12:17:41 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_var
{
	char	*name;
	char	*content;
}			t_var;

t_env	*newnode(char *data, char *data2);
t_env	*set_env(char **envp);

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

char	**read_line(char *string);
char	*ft_cpy_content(char *str);
char	*ft_cpy_name(char *str);

char	**list_to_array(t_env *list);
#endif
