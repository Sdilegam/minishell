# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/05/23 14:30:24 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	cc -c $< -o $@

$(NAME) : $(OBJS)
		cc -Wall -Werror -Wextra $(OBJS) -o $(NAME) -lreadline

clean :
		rm -rf $(OBJS)

fclean : clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
