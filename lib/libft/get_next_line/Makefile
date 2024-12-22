# Compiler & Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
OBJ_DIR = ../obj/

# Sources & Objects & Includes & Targets
SOURCES = get_next_line.c get_next_line_utils.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)
INCLUDE = get_next_line.h
NAME = libgnl.a

# Rules & Recipes
all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

obj: $(OBJECTS)

$(OBJ_DIR)%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -I.$(INCLUDE) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# PHONY rules
.PHONY: all clean fclean re