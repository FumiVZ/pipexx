NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g  
CC = cc
BUILD_DIR = build

SRC =	$(wildcard code/*/*.c) \
		$(wildcard builtins/*/*.c) \

LIBFT = libft/libft.a
LIB_PATH = libft
HEADER_PATH = code/header

OBJECTS = $(SRC:%.c=$(BUILD_DIR)/%.o)
HEADER = $(wildcard code/header/*.h)

all: $(BUILD_DIR) $(LIBFT) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/code
	mkdir -p $(BUILD_DIR)/bonus
	mkdir -p $(BUILD_DIR)/builtins
	mkdir -p $(BUILD_DIR)/builtins/echo
	mkdir -p $(BUILD_DIR)/builtins/cd
	mkdir -p $(BUILD_DIR)/builtins/pwd
	mkdir -p $(BUILD_DIR)/builtins/export
	mkdir -p $(BUILD_DIR)/builtins/unset
	mkdir -p $(BUILD_DIR)/builtins/env
	mkdir -p $(BUILD_DIR)/builtins/exit
	mkdir -p $(BUILD_DIR)/builtins/history
	mkdir -p $(BUILD_DIR)/code/split_line
	mkdir -p $(BUILD_DIR)/code/split_command
	mkdir -p $(BUILD_DIR)/code/error
	mkdir -p $(BUILD_DIR)/code/prompt
	mkdir -p $(BUILD_DIR)/code/prompt
	mkdir -p $(BUILD_DIR)/code/exec


$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) -lreadline -lncurses

$(BUILD_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH) -I$(LIB_PATH)

$(LIBFT):
	$(MAKE) -C $(LIB_PATH) 

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re 
