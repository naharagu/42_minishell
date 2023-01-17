CC			=	gcc
CFLAGS 	=	-Wall -Werror -Wextra -g -fsanitize=address
# CFLAGS 	=	-Wall -Werror -Wextra
RL_FLAGS 	=	-I $(shell brew --prefix readline)/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
NAME		=	minishell
SRCS		= 	main.c
OBJS_DIR	=	./obj/
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)
LIB_DIR		= 	./libft
LIB			=	./libft/libft.a

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) -o $(NAME) $(LIB)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
