# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
OBJ_DIR = ../obj/

# Sources and targets
SOURCES = 	ft_printf.c char_parser.c str_parser.c ptr_parser.c decimal_parser.c\
			unsigned_parser.c low_hexa_parser.c up_hexa_parser.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)
INCLUDE = ft_printf.h
NAME = libftprintf.a

# Rules and recipes
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