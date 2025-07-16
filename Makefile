NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I$(INCLUDE)

SRC_DIR := src
BUILD_DIR := obj
INCLUDE := include

SRC := main.c src/utils.c src/threads.c src/init_structs.c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean:
	@rm -rf $(BUILD_DIR)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re