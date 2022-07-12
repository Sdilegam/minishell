# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 17:28:09 by abkasmi           #+#    #+#              #
#    Updated: 2022/07/12 17:52:00 by sdi-lega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
		ft_utils.c \

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

all : $(NAME)

$(NAME) : $(OBJS)
			@ ar rc $(NAME) $(OBJS)
			@ ranlib $(NAME)

.c.o:
		@ gcc -Wall -Werror -Wextra -c $< -o $(<:.c=.o)

clean:
		@ rm -f $(OBJS)

fclean:	clean
		@ rm -f $(NAME)

re:		@ fclean all

.PHONY:		all clean fclean re
