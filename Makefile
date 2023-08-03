# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 01:40:01 by akhellad          #+#    #+#              #
#    Updated: 2023/08/04 01:25:16 by agaley           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

SRCS_DIR = srcs/
OBJS_DIR = objs/
TMP_DIR = tmp/
LIBFT_DIR = libft/
INC_DIR = includes/

SRCS    = main.c \
		  execute.c \
		  execute_utils.c \
		  lexers.c \
		  utils.c \
		  loop.c \
		  envp.c \
		  parser.c \
		  clear_lexer.c \
		  errors.c \
		  redirs.c \
		  expand.c \
		  check_files.c \
		  here_doc.c \
		  large_execute.c \
		  lexers_utils.c \
		  quotes.c \
		  spaces.c \
		  cmds_infos.c \
		  expand_utils.c \
		  builtins.c \
		  cd_built.c \
		  env_built.c \
		  exit_built.c \
		  signals.c

OBJS    = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

HEADER  = -Iincludes
LIBFT   = -Llibft -lft
INC     = ${INC_DIR}*.h libft/includes/libft.h

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g3

LIB_A   = libft/libft.a


all:        ${NAME}

tmp:        force
			@mkdir -p $(TMP_DIR)

${LIB_A}:   force libft/includes/libft.h
			@make all -C ./libft

${NAME}:    ${OBJS} ${LIB_A} tmp
			@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}"
			@$(CC) ${OBJS} -Llibft -lft -lreadline -o ${NAME}

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c Makefile ${INC}
			@mkdir -p $(OBJS_DIR)
			@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
			@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@

check:
			norminette ${SRCS_DIR} ${INC_DIR}

clean:
			@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${OBJS}"
			@make clean -C ./libft
			@rm -f ${OBJS}
			@rm -rf ${TMP_DIR}

fclean:    	clean
			@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
			@make fclean -C ./libft
			@rm -f ${NAME}
			@rm -rf $(OBJS_DIR)

re:         fclean all

.PHONY: all clean fclean re force
