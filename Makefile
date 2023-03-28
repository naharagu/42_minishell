# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 11:05:34 by shimakaori        #+#    #+#              #
#    Updated: 2023/03/28 10:48:34 by naharagu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
RL_FLAGS 	=	-lreadline -lhistory -L$(shell brew --prefix readline)/lib -L/usr/local/Cellar/readline/8.2.1/lib -L/usr/local/opt/readline/lib
INCLUDE		=   -I include -I $(LIB_DIR) -I $(shell brew --prefix readline)/include -I/usr/local/opt/readline/include
CFLAGS 		=	-Wall -Werror -Wextra -g -fsanitize=address $(INCLUDE)
# CFLAGS 	=	-Wall -Werror -Wextra $(INCLUDE)
SRCS		= 	srcs/main.c							\
				srcs/builtin/ft_cd.c				\
				srcs/builtin/ft_echo.c				\
				srcs/builtin/ft_env.c				\
				srcs/builtin/ft_exit.c				\
				srcs/builtin/ft_export.c			\
				srcs/builtin/ft_pwd.c				\
				srcs/builtin/ft_unset.c				\
				srcs/environ/add_envlist.c			\
				srcs/environ/create_array.c			\
				srcs/environ/environ.c				\
				srcs/execute/execute.c				\
				srcs/execute/execute_builtin.c		\
				srcs/execute/path.c					\
				srcs/execute/pipe.c					\
				srcs/lexer/bool.c					\
				srcs/lexer/error.c					\
				srcs/lexer/lexer.c					\
				srcs/lexer/mslist.c					\
				srcs/parser/add_cmdlist.c			\
				srcs/parser/add_execlist.c			\
				srcs/parser/check_type.c			\
				srcs/parser/exec_lstnew.c			\
				srcs/parser/expansion.c				\
				srcs/parser/parser.c				\
				srcs/redirect/add_redlist.c		    \
				srcs/redirect/heredoc.c			    \
				srcs/redirect/redirect_check.c		\
				srcs/redirect/redirect_prepare.c	\
				srcs/redirect/redirect_set.c		\
				srcs/test/print_error.c			    \
				srcs/test/print_list.c				\
				srcs/utils/exec_lstclear.c			\
				srcs/utils/list_to_argv.c			\
				srcs/utils/signal.c				    \
				srcs/utils/utils.c
OBJS		=	$(SRCS:%.c=%.o)
LIB_DIR		= 	./libft
LIB			=	./libft/libft.a

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $^ $(RL_FLAGS) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
