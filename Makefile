# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/06/06 18:12:11 by abkasmi          ###   ########.fr        #
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

LDFLAGS = readline-lib/libreadline.a readline-lib/libhistory.a
LDFLAGS += $(LIBRARY) 
LDFLAGS += -ltermcap

# LDFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I ./includes/
CFLAGS += -I ./readline-lib/

all : $(LIBRARY) $(NAME) 

%.o : %.c
	cc $(CFLAGS) -c $< -o $@

$(LIBRARY) : 
	$(MAKE) -C $(dir $(LIBRARY))

# bye bye	
# $(OBJS) -o $(NAME) ${addprefix -L, ${dir ${LIBRARY}}} ${addprefix -l, ${patsubst lib%.a, %, ${notdir ${LIBRARY}}}}

$(NAME) : $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean :
	$(MAKE) -C $(dir $(LIBRARY)) clean
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) -C $(dir $(LIBRARY)) fclean
	rm -rf $(NAME)

re : fclean all

debug: CFLAGS += -g -fsanitize=address 
debug: re

.PHONY : all clean fclean re
