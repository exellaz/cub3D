# Directories
LIBFT_DIR = libft/
FT_PRINTF_DIR = ft_printf/
GNL_DIR = get_next_line/
OBJ_DIR = obj/

# Target
LIBFT = $(LIBFT_DIR)libft.a
FT_PRINTF = $(FT_PRINTF_DIR)libftprintf.a
GET_NEXT_LINE = $(GNL_DIR)libgnl.a
NAME = libft.a

# Rules & Recipes
all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(FT_PRINTF) $(GET_NEXT_LINE)
	ar rc $(NAME) $(OBJ_DIR)*.o

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR) obj

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR) obj

$(GET_NEXT_LINE):
	make -C $(GNL_DIR) obj

clean:
	rm -f $(OBJ_DIR)*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(FT_PRINTF)
	rm -f $(GET_NEXT_LINE)

re: fclean all

# PHONY rules
.PHONY: all clean fclean re
