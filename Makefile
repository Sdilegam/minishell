# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/06/06 15:01:02 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	srcs/main.c\
		srcs/header.c\
		srcs/read_line.c\
		srcs/list_to_array.c\
		srcs/minishell_utils.c\
		srcs/signal.c\
		srcs/builtins/set_env.c\
		srcs/builtins/echo.c\
		srcs/builtins/cd.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/unset.c\

OBJS = $(SRCS:.c=.o)

LIBRARY = ft_printf/libftprintf.a

all : $(NAME)

%.o : %.c
	cc -Iincludes/ -c $< -o $@ -g

$(NAME) : $(OBJS) ${LIBRARY}
		cc -Wall -Werror -Wextra $(OBJS) -o $(NAME) ${addprefix -L, ${dir ${LIBRARY}}} ${addprefix -l, ${patsubst lib%.a, %, ${notdir ${LIBRARY}}}} -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -g

clean :
		rm -rf $(OBJS)

fclean : clean
			make fclean -C ft_printf 
			rm -rf $(NAME)
			
ft_printf/libftprintf.a :
					make -C ft_printf

re : fclean all

.PHONY : all clean fclean re
