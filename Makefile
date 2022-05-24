# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/05/24 14:51:37 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	srcs/main.c\
		srcs/header.c\
		srcs/read_line.c\
		srcs/minishell_utils.c\
		srcs/builtins/echo.c\
		srcs/builtins/cd.c\
		srcs/builtins/env.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	cc -Iincludes/ -c $< -o $@ -g

$(NAME) : $(OBJS)
		cc -Wall -Werror -Wextra $(OBJS) -o $(NAME) -lreadline -g

clean :
		rm -rf $(OBJS)

fclean : clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
