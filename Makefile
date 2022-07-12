# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/07/12 15:53:48 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	srcs/main.c\
		srcs/header.c\
		srcs/parse_variables.c\
		srcs/list_to_array.c\
		srcs/minishell_utils.c\
		srcs/signal.c\
		srcs/pipe.c\
		srcs/quotes_handling.c\
		srcs/here_doc.c\
		srcs/parsing.c\
		srcs/command_list.c\
		srcs/builtins/set_env.c\
		srcs/builtins/echo.c\
		srcs/builtins/cd.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/unset.c\
		srcs/builtins/exit.c\
		srcs/outp_redir.c\
		srcs/path.c\
		srcs/ft_itoa.c\
		srcs/parse_p_redi.c\
		srcs/input_redir.c\

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

debug: CFLAGS += -g
debug: re

.PHONY : all clean fclean re
