# Compiler & Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
INC = -I.

# Directories
SRC_DIR = src
OBJ_DIR = ../obj

vpath %.c $(SRC_DIR)

# Files
SRC = $(foreach module, $(SRC_DIR), $(wildcard $(module)/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = libmem.h
BIN = libmem.a

all : $(BIN)

$(BIN) : $(OBJ)
	ar rcs $@ $^
	ranlib $@

obj : $(OBJ)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm $(BIN)

re : fclean all

.PHONY : all clean fclean re
