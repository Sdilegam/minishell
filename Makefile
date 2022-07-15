# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 13:27:32 by abkasmi           #+#    #+#              #
#    Updated: 2022/07/15 10:45:36 by abkasmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
OBJS_DIR = objects/
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
		srcs/outp_redir.c\
		srcs/outp_redir_append.c\
		srcs/path.c\
		srcs/ft_itoa.c\
		srcs/parse_p_redi.c\
		srcs/input_redir.c\
		srcs/builtins/set_env.c\
		srcs/builtins/echo.c\
		srcs/builtins/cd.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/unset.c\
		srcs/builtins/exit.c\
		srcs/builtins/pwd.c\
		srcs/check_shlvl.c\
		srcs/atoi.c\
		srcs/path2.c\
		srcs/get_final_len.c\
		srcs/ft_calloc.c\
		srcs/ft_free.c\
		srcs/init_prompt.c\
		srcs/string_checking.c\
		srcs/parsing2.c

OBJS = ${addprefix ${OBJS_DIR}, ${notdir ${SRCS:.c=.o}}}

LIBRARY = ft_printf/libftprintf.a

#LDFLAGS = readline-lib/libreadline.a readline-lib/libhistory.a
#LDFLAGS += -ltermcap
LDFLAGS = -lreadline -L ~/.brew/opt/readline/lib
LDFLAGS += $(LIBRARY) 


CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I ./includes/ -I ~/.brew/opt/readline/include

all : $(LIBRARY) $(NAME) 


${OBJS_DIR}%.o:	srcs/%.c
		@ echo "\033[KCreating common object file:\n\033[K\"\033[1;32m${@F:.c=.o}\033[m\".\033[2A"
		@ cc $(CFLAGS) -c $< -o $@
		@ sleep 0.1
		
${OBJS_DIR}%.o:	srcs/builtins/%.c
		@ echo "\033[KCreating builtins object file:\n\033[K\"\033[1;32m${@F:.c=.o}\033[m\".\033[2A"
		@ cc $(CFLAGS) -c $< -o $@
		@ sleep 0.1

$(OBJS_DIR) :
			mkdir $(OBJS_DIR)
$(LIBRARY) : 
	@ make -C $(dir $(LIBRARY))
	@ echo "Library successfully created: \"\033[1;32m${patsubst %/, %, ${dir ${LIBRARY}}}\033[m\"."

$(NAME) : ${OBJS_DIR} $(OBJS)
	@ echo "\r\033[KSuccessfully found objects files. (\033[1;32m${notdir ${OBJS}}\033[m)"
	@ cc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@ sleep 0.3
	@ echo "Executable successfully created: \"\033[1;32m${NAME}\033[m\"."

clean :
	@ make -C $(dir $(LIBRARY)) clean
	@ echo "\rRemoving objects files (${notdir ${OBJS}}).\033[K\c"
	@ rm -rf ${OBJS} 
	@ sleep 0.3
	@ echo "\r\033[KRemoved objects files. (\033[1;31m${notdir ${OBJS}}\033[m)"

fclean : clean
	@ make -C $(dir $(LIBRARY)) fclean
	@ echo "\r\033[KRemoving executables (${NAME}).\c"
	@ rm -rf ${NAME}
	@ sleep 0.3
	@ echo "\r\033[KRemoved executables: \"\033[1;31m${NAME}\033[m\"."

re : fclean all

debug: CFLAGS += -g
debug: re

.PHONY : all clean fclean re
