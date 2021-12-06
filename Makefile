SRCS_DIR		= src/
SRCS			= main.c
SRCS_WITHPATH	= ${addprefix ${SRCS_DIR}, ${SRCS}}
OBJS			= ${SRCS_WITHPATH:.c=.o}
LIBF			= libft
LIB				= ${LIBF}/libft.a

INCLUDE = libft/libft.h libft/libftprintf.h minishell.h
NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

all:		${NAME}

%.o: %.c ${INCLUDE}
			${CC} -c ${CFLAGS} -iquote ${LIBF} -o $@ $<

${NAME}:	${OBJS} ${LIB} ${INCLUDES}
			${CC} ${OBJS} ${LIB} -lreadline -iquote ${LIBF} -o ${NAME}

${LIB}:
			cd ${LIBF} && ${MAKE}

relibft:
			cd ${LIBF} && ${MAKE} re

clean:
			cd ${LIBF} && ${MAKE} clean
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

libftclean:
			cd ${LIBF} && ${MAKE} fclean

re:			fclean all

.PHONY: all clean fclean re
