# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 11:05:34 by shimakaori        #+#    #+#              #
#    Updated: 2023/02/27 12:35:58 by shimakaori       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
C_FLAGS 	=	-Wall -Werror -Wextra -g -fsanitize=address
# C_FLAGS 	=	-Wall -Werror -Wextra
RL_FLAGS 	=	-I $(shell brew --prefix readline)/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE		=   -I include -I $(LIB_DIR)
VPATH 		=   srcs
SRCS		= 	main.c        \
				lexer.c       \
				parser.c      \
				expansion.c   \
				redirect.c    \
				red_out.c     \
				red_append.c  \
				red_heredoc.c \
				red_in.c      \
				cmd_exec.c    \
				error.c       \
				utils.c       \
				mslist.c 	  \
				execlist_1.c  \
				execlist_2.c  \
				print.c
OBJS_DIR	=	./obj/
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)
LIB_DIR		= 	./libft
LIB			=	./libft/libft.a

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(C_FLAGS) $(RL_FLAGS) $(OBJS) -o $(NAME) $(LIB)

$(OBJS_DIR)%.o: %.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: $(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
