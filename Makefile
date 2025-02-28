# Compiler & Flags
CC = clang
CFLAGS = -O3 #-Wall -Werror -Wextra -O3
INC = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
LIB = -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lft -lm -lX11 -lXext

# Directories
LIBFT_DIR = lib/libft
MLX_DIR = lib/minilibx-linux
SRC_DIR = src src/map src/utils
OBJ_DIR = obj

vpath %.c $(SRC_DIR)

# Files
SRC = $(foreach module, $(SRC_DIR), $(wildcard $(module)/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = $(wildcard include/*.h) $(wildcard $(LIBFT_DIR)/*.h) $(wildcard $(MLX_DIR)/*.h)
MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
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

valgrind : $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)

fsan:
	$(CC) $(CFLAGS) -fsanitize=address -g3 $(INC) $(OBJ) $(LIB) -o $(BIN)

debug: CFLAGS := -D DEBUG=1
debug: $(BIN)

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(BIN)
	rm -f $(MLX_DIR)/$(MLX)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all valgrind fsan clean fclean re
