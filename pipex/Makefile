# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 17:18:11 by mwen              #+#    #+#              #
#    Updated: 2021/10/12 20:30:33 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	src/
SRCS			=	main.c check.c error.c init.c free.c\
					ft_split.c ft_calloc.c ft_strdup.c ft_strchr.c ft_strnstr.c\
					ft_strjoin.c
SRCS_WITHPATH	=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS			=	$(SRCS_WITHPATH:.c=.o)
SRCS_DIR_B		=	bonus/
SRCS_B			=	main_bonus.c check_bonus.c error_bonus.c init_bonus.c \
					free_bonus.c\
					ft_split_bonus.c ft_calloc_bonus.c ft_strdup_bonus.c\
					ft_strchr_bonus.c ft_strnstr_bonus.c ft_strjoin_bonus.c
SRCS_WITHPATH_B	=	$(addprefix $(SRCS_DIR_B), $(SRCS_B))
OBJS_B			=	$(SRCS_WITHPATH_B:.c=.o)
NAME			=	pipex
CC				=	gcc
RM				= 	rm -f
FLAGS			=	-Wall -Werror -Wextra

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(FLAGS) $(OBJS) -o pipex

bonus:			$(OBJS_B)
				@$(CC) $(FLAGS) $(OBJS_B) -o pipex

clean:			
				@$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
				@$(RM) pipex

re:				fclean all

.PHONY: all clean fclean re