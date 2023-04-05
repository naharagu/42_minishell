NAME		=	minishell
CC			=	gcc
RL_FLAGS 	=	-lreadline -lhistory -L$(shell brew --prefix readline)/lib -L/usr/local/Cellar/readline/8.2.1/lib -L/usr/local/opt/readline/lib
INCLUDE		=   -I include -I $(LIB_DIR) -I $(shell brew --prefix readline)/include -I/usr/local/opt/readline/include
CFLAGS 		=	-Wall -Werror -Wextra $(INCLUDE)
SRCS		= 	srcs/main.c							\
				srcs/builtin/ft_cd.c				\
				srcs/builtin/ft_echo.c				\
				srcs/builtin/ft_env.c				\
				srcs/builtin/ft_exit.c				\
				srcs/builtin/ft_export.c			\
				srcs/builtin/ft_pwd.c				\
				srcs/builtin/ft_unset.c				\
				srcs/environ/create_array.c			\
				srcs/environ/env_getter.c			\
				srcs/environ/environ.c				\
				srcs/execute/execute.c				\
				srcs/execute/execute_builtin.c		\
				srcs/execute/path.c					\
				srcs/execute/pipe.c					\
				srcs/lexer/bool.c					\
				srcs/lexer/error.c					\
				srcs/lexer/lexer.c					\
				srcs/list/add_cmdlist.c				\
				srcs/list/add_envlist.c				\
				srcs/list/add_execlist.c			\
				srcs/list/add_redlist.c		    	\
				srcs/list/exec_lstnew.c				\
				srcs/list/exec_lstclear.c			\
				srcs/list/mslist.c					\
				srcs/parser/check_type.c			\
				srcs/parser/expansion.c				\
				srcs/parser/expand_cmd.c			\
				srcs/parser/expand_red.c			\
				srcs/parser/parser.c				\
				srcs/redirect/heredoc.c			    \
				srcs/redirect/redirect_check.c		\
				srcs/redirect/redirect_prepare.c	\
				srcs/redirect/redirect_set.c		\
				srcs/signal/signal_handler.c		\
				srcs/signal/signal_set.c			\
				srcs/test/print_list.c				\
				srcs/utils/argv.c					\
				srcs/utils/print_error.c			\
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

sanitize: CFLAGS += -g -fsanitize=address
sanitize: re

norm:
	norminette $(SRCS)
normall:
	norminette $(SRCS) $(LIB_DIR)/*.c $(LIB_DIR)/*.h include/*.h

.PHONY: all clean fclean re sanitize norm normall
