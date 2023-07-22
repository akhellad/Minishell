NAME 	= 	libft.a

SRCDIR	=	./src
INCDIR	=	./includes
BINCDIR =	./bonus_includes
OBJDIR	=	./obj
BONDIR	=	./bonus
BONOBJDIR = ./bonus_obj


SRC = ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c ft_isdigit.c ft_memset.c ft_strdup.c \
		ft_strncmp.c ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c ft_bzero.c ft_itoa.c \
		ft_putendl_fd.c ft_strjoin.c ft_strrchr.c ft_calloc.c ft_memchr.c ft_putnbr_fd.c  ft_strlcat.c \
		ft_strtrim.c ft_isalnum.c ft_memcmp.c ft_putstr_fd.c  ft_strlcpy.c ft_substr.c ft_isalpha.c ft_memcpy.c \
		ft_split.c ft_strlen.c  ft_tolower.c get_next_line.c


BONUS=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
		ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c


OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
BONUSOBJ =  $(addprefix $(BONOBJDIR)/,$(BONUS:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ARRC = ar rcs
HEADER = libft.h

all: obj ${NAME}

obj:
	@mkdir -p ${OBJDIR}

obj_bonus:
	@mkdir -p ${BONOBJDIR}

${OBJDIR}/%.o:${SRCDIR}/%.c includes/libft.h
	@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) ${CFLAGS} -I ${INCDIR} -o $@ -c $<

${BONOBJDIR}/%.o:${BONDIR}/%.c
	@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) ${CFLAGS} -I ${INCDIR} -o $@ -c $<

${NAME}: ${OBJ}
	@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 
	@${ARRC} ${NAME} ${OBJ}

bonus:	obj_bonus $(BONUSOBJ) 
	@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 
	@${ARRC} ${NAME} ${BONUSOBJ}
	
clean:
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: $(OBJDIR)" $<
	@rm -rf ${OBJ} $(BONUSOBJ) ${OBJDIR} ${BONOBJDIR}

fclean:	clean
	@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
	@rm -rf $(NAME)

re: fclean all
