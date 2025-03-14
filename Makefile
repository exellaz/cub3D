# Compiler & Flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3
INC = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
LIB = -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lft -lm -lX11 -lXext

# Directories
LIBFT_DIR = lib/libft
MLX_DIR = lib/minilibx-linux
OBJ_DIR = obj

# Files
SRC = src/events/controls.c src/events/event_handlers.c src/events/event_hooks.c \
	  src/map/door.c src/map/map_utils-1.c src/map/map_utils.c src/map/map_valid.c src/map/map.c src/map/path.c src/map/rgb.c src/map/spawn.c src/map/textures.c \
	  src/minimap/minimap.c src/minimap/minimap_player.c src/minimap/minimap_utils.c \
	  src/raycasting/draw_floor_and_ceiling.c src/raycasting/draw_wall.c src/raycasting/get_texture_data.c src/raycasting/raycaster.c src/raycasting/render_floor_and_ceiling.c src/raycasting/render_open_door.c src/raycasting/render_walls.c \
	  src/sprites/init_sprites.c src/sprites/render_sprites.c \
	  src/utils/pixel_utils.c src/utils/utils-1.c src/utils/utils.c \
	  src/error.c src/framerate.c src/main.c src/setup.c src/validation.c
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = include/cub3D.h include/defines.h include/error.h include/events.h include/map.h include/minimap.h include/raycast.h include/types.h include/utils.h \
		 lib/libft/c_libft.h \
		 lib/minilibx-linux/mlx.h lib/minilibx-linux/mlx_int.h
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

$(OBJ_DIR)/%.o : src/**/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o : src/%.c $(HEADER)
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

fullbright: CFLAGS += -D FULLBRIGHT=1
fullbright: $(MLX) $(LIBFT) $(LIBMEM) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(BIN)

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
