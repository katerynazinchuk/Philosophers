NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFlags += -I$(INCLUDE)

SRC_DIR := src
BUILD_DIR := obj
INCLUDE := include

SRC := $()
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)