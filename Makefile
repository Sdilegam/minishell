# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/05/23 15:56:13 by sdi-lega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	srcs/main.c\
		srcs/header.c

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
