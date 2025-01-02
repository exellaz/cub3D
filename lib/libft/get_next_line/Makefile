# Compiler & Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
OBJ_DIR = ../obj

# Sources & Objects & Includes & Targets
SOURCES = get_next_line.c get_next_line_utils.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)
HEADER = get_next_line.h ../libmem/libmem.h
INCLUDE = -I. -I../libmem
NAME = libgnl.a

# Rules & Recipes
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	ranlib $(NAME)

obj: $(OBJECTS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# PHONY rules
.PHONY: all clean fclean re
