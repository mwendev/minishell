# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 13:50:28 by mwen              #+#    #+#              #
#    Updated: 2021/12/11 22:24:44 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	clang
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf
INCLUDE			=	libft/libft.h minishell.h

SRCS_LIST		=	main.c builtin.c error.c check.c execute.c
SRCS_DIR		=	src/
SRCS			=	${addprefix ${SRCS_DIR}, ${SRCS}}

OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS_DIR		=	obj/
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST)) $(GNL:.c=.o)

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_DIR		=	libft/

GREEN			=	\033[0;32m
RED				=	\033[0;31m
RESET			=	\033[0m

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS)
				@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c 
				@$(CC) $(FLAGS) -c -I$(SRCS_DIR) $< -o $@

$(LIBFT):
				@echo "$(GREEN)Compiling $(LIBFT)...$(RESET)"
				@$(MAKE) -sC $(LIBFT_DIR)

clean:
			@$(MAKE) -sC $(LIBFT_DIR) clean
			@$(RM) $(OBJS_DIR)
			@echo "$(RED)cleaned$(RESET)"

fclean:		clean
			@$(MAKE) -sC $(LIBFT_DIR) fclean
			@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
