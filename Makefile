CC			=	gcc
C_FLAGS 	=	-Wall -Werror -Wextra -g -fsanitize=address
# C_FLAGS 	=	-Wall -Werror -Wextra
LIB_DIR		= 	./libft
SRCS		= 	main.c
NAME		=	minishell
OBJS_DIR	=	./obj/
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)
LIB			=	./libft/libft.a

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(C_FLAGS) $(OBJS) -o $(NAME) $(LIB)

$(OBJS_DIR)%.o: %.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
