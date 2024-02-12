NAME = pipex
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
libft = ./libft
CC = cc
SRC = pipex.c \
	utils.c 

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) libft $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(libft)

-include $(DEPS)

$(NAME): $(OBJ) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(libft) -lft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft:
	make -C $(libft)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(libft) clean

fclean: clean
	rm -f $(NAME)
	make -C $(libft) fclean

re: fclean all

.PHONY: all clean fclean re libft
