# Compiler & Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
INC = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(LIBMEM_DIR)
LIB = -L$(MLX_DIR) -L$(LIBFT_DIR) -L$(LIBMEM_DIR) -lmlx -lft -lmem -lm -lX11 -lXext

# Directories
LIBMEM_DIR = lib/libmem
LIBFT_DIR = lib/libft
MLX_DIR = lib/minilibx-linux
SRC_DIR = src
OBJ_DIR = obj

vpath %.c $(SRC_DIR)

# Files
SRC = $(foreach module, $(SRC_DIR), $(wildcard $(module)/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = $(wildcard include/*.h) $(wildcard $(LIBMEM)/*.h) $(wildcard $(LIBFT_DIR)/*.h) $(wildcard $(MLX_DIR)/*.h)
MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
LIBMEM = $(LIBMEM_DIR)/libmem.a
BIN = cub3D

# # Debug
# $(info SRC: $(SRC))
# $(info OBJ: $(OBJ))
# $(info HEADER: $(HEADER))
# $(info INC: $(INC))

all : $(BIN)

$(BIN) : $(MLX) $(LIBFT) $(LIBMEM) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(BIN)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(MLX) :
	make -C $(MLX_DIR)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(LIBMEM) :
	make -C $(LIBMEM_DIR)

valgrind : $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)

fsan:
	$(CC) $(CFLAGS) -fsanitize=address $(INC) $(OBJ) $(LIB) -o $(BIN)


clean :
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMEM_DIR) clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(BIN)
	rm -f $(MLX_DIR)/$(MLX)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBMEM_DIR) fclean

re : fclean all

.PHONY: all valgrind fsan clean fclean re
