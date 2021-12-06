# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 12:00:25 by mwen              #+#    #+#              #
#    Updated: 2021/06/18 17:13:54 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memccpy.c \
					ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
					ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c \
					ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_strtrim.c
SRCS_B			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstnew.c ft_lstsize.c ft_lstmap.c
OBJS			=	${SRCS:.c=.o}
OBJS_B			=	${SRCS_B:.c=.o}
HEADER_FILES	=	libft.h
NAME			=	libft.a
CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Werror -Wextra

all:			$(NAME)

$(NAME):		$(OBJS) $(OBJS_B)
				ar rcs $(NAME) $(OBJS) $(OBJS_B)
				$(RM) $(OBJS) $(OBJS_B)

bonus:			$(OBJS) $(OBJS_B)
				ar rcs $(NAME) $(OBJS) $(OBJS_B)
				$(RM) $(OBJS) $(OBJS_B)

%.o: 			%.c	$(HEADER_FILES)
				$(CC) -c $(CFLAGS) -o $@ $<

clean:
				$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all %.o clean fcloean re bonus
