/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:19:45 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/24 14:20:05 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>


void	print_header(void);
void	ft_cd(char **path);
void	ft_putstr(char *str);
void	ft_pwd(void);

int		is_space(char chara);
int		is_alpha(char chara);
int		count_words(char *string);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(char **str);

char	**read_line(char *string);

#endif
