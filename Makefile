# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 11:05:34 by shimakaori        #+#    #+#              #
#    Updated: 2023/03/24 10:18:22 by naharagu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
C_FLAGS 	=	-Wall -Werror -Wextra -g -fsanitize=address
# C_FLAGS 	=	-Wall -Werror -Wextra
RL_FLAGS 	=	-lreadline -lhistory -L$(shell brew --prefix readline)/lib -L/usr/local/Cellar/readline/8.2.1/lib -L/usr/local/opt/readline/lib
INCLUDE		=   -I include -I $(LIB_DIR) -I $(shell brew --prefix readline)/include -I/usr/local/opt/readline/include
# RL_FLAGS 	=	-I $(shell brew --prefix readline)/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
# INCLUDE		=   -I include -I $(LIB_DIR)
VPATH 		=   srcs
SRCS		= 	main.c          \
				signal.c        \
				lexer.c         \
				bool.c          \
				parser.c        \
				check_type.c    \
				expansion.c     \
				cmd_exec.c      \
				utils.c         \
				mslist.c 	    \
				exec_lstnew.c   \
				exec_lstclear.c \
				add_execlist.c  \
				add_cmdlist.c   \
				add_redlist.c   \
				add_envlist.c   \
				error.c         \
				print_error.c   \
				ft_exit.c       \
				ft_cd.c         \
				list_to_argv.c  \
				print_list.c \
				create_args_array.c \
				execute_cmd.c	\
				path.c			\
				pipe.c			\
				redirect_check.c		\
				redirect_prepare.c		\
				redirect_set.c
OBJS_DIR	=	./obj/
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)
LIB_DIR		= 	./libft
LIB			=	./libft/libft.a

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(C_FLAGS) $(RL_FLAGS) $(OBJS) -o $(NAME) $(LIB)

$(OBJS_DIR)%.o: %.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(C_FLAGS) $(INCLUDE) -o $@ -c $<

all: $(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
