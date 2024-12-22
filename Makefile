# Compiler & Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

# Directories
LIBFT_DIR = lib/libft
MLX_DIR = lib/minilibx-linux
SRC_DIR = src
OBJ_DIR = obj

vpath %.c $(SRC_DIR)

# Files
SRC = $(foreach module, $(SRC_DIR), $(wildcard $(module)/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = $(wildcard include/*.h) $(wildcard $(LIBFT_DIR)/*.h) $(wildcard $(MLX_DIR)/*.h)
INC = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX = libmlx.a
LIBFT = libft.a
BIN_LINK = -L. -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lft -lm -lX11 -lXext
EXE = cub3D

# # Debug
# $(info SRC: $(SRC))
# $(info OBJ: $(OBJ))
# $(info HEADER: $(HEADER))
# $(info INC: $(INC))

all : $(EXE)

$(EXE) : $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(BIN_LINK) -o $(EXE)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(MLX) :
	make -C $(MLX_DIR)

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean :
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(EXE)
	rm -f $(MLX_DIR)/$(MLX)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re
