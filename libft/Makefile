SRCS	=	ft_calloc.c ft_isascii.c ft_itoa.c ft_memcmp.c ft_memset.c ft_putnbr_fd.c ft_strchr.c \
			ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c ft_atoi.c \
			ft_isalnum.c ft_isdigit.c ft_isinarray.c \
			ft_memccpy.c ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlcpy.c ft_strncmp.c \
			ft_strtrim.c ft_toupper.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memchr.c ft_memmove.c \
			ft_putendl_fd.c ft_split.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstmap.c ft_lstclear.c ft_lstlast.c ft_lstsize.c \
			ft_lstadd_front.c ft_lstiter.c ft_lstnew.c ft_lstpop_front.c ft_lstpop_back.c \
			ft_lstmin.c ft_lstmax.c \
			ft_printf.c ft_printf_handlers.c ft_printf_flag_set.c ft_putnbr_base.c \
			ft_printf_flagmod.c ft_printf_printstr.c ft_printf_numbers.c \
			ft_printf_putnbr.c ft_printf_putnbr_utils.c ft_printf_hexa.c \
			get_next_line.c get_next_line_utils.c
OBJ		= ${SRCS:.c=.o}

INCLUDE = libft.h libftprintf.h get_next_line.h
NAME	= libft.a
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

all:		${NAME}

%.o: %.c ${INCLUDE}
			${CC} -c ${CFLAGS} -o $@ $<

${NAME}:	${OBJ} ${INCLUDE}
			ar rc ${NAME} ${OBJ}

clean:
			${RM} ${OBJ} ${OBJ}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
