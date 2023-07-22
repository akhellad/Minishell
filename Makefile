# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 01:40:01 by akhellad          #+#    #+#              #
#    Updated: 2023/07/22 06:56:25 by akhellad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS 	= srcs/main.c srcs/execute.c srcs/history.c srcs/parser.c srcs/utils.c
OBJS 	= ${SRCS:.c=.o}

HEADER	= -Iincludes
LIBFT   = -Llibft -lft
INC		= includes/*.h libft/includes/libft.h

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g3

LIB_A   = libft/libft.a


all: 		${NAME}

${LIB_A}:	force libft/includes/libft.h
			@make all -C ./libft

${NAME}:	${OBJS} ${LIB_A}
					@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 
					@$(CC) ${OBJS} -Llibft -lft -o ${NAME}

${OBJS}: %.o: %.c Makefile ${INC} 
				@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
				@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@

clean:
					@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${OBJS}"
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
					@make fclean -C ./libft
					@rm -f ${NAME}

re:			fclean all


.PHONY: all clean fclean re force