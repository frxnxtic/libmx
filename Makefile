# Compiler and flags
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIB_NAME = libmx.a
HEADER = $(INC_DIR)/libmx.h

# Rules
all: $(LIB_NAME)

# Creating the library archive
$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $^

# Compile C files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean the object and archive files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything including the compiled library
fclean: clean
	rm -f $(LIB_NAME)

# Recompile everything
re: fclean all

# PHONY targets to avoid conflict with file names
.PHONY: all clean fclean re

