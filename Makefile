NAME = cub3d
CC = cc
UNAME_S := $(shell uname -s)
CFLAGS = -Wall -Wextra -Werror -g -lm #-fsanitize=address
MINILIBX_TGZ_NAME = MiniLibX.tgz
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://github.com/42Paris/minilibx-linux
	FLAGS_MINILIBX = -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MINILIBX_DIR = ./minilibx-linux
else ifeq ($(UNAME_S), Darwin)
	LIB_URL = https://cdn.intra.42.fr/document/document/26193/minilibx_opengl.tgz
	FLAGS_MINILIBX = -Lmlx -framework OpenGL -framework AppKit
	MINILIBX_DIR = ./minilibx_opengl_20191021
endif
		
SRCS =	src/main.c \
		src/parsing/parsing_file.c \
		src/parsing/parsing_map.c \
		src/parsing/textures.c \
		src/parsing/wall-checks.c \
		src/parsing/parsing_utils.c \
		src/parsing/map-checks.c \
		src/rendering/init_window.c \
		src/rendering/init_canvas.c \
		src/rendering/player.c \
		src/rendering/events.c \
		src/rendering/render_utils.c \
		src/Math-functions/distance.c \
		src/Math-functions/new_pos.c \
		src/Math-functions/radians_utils.c \
		src/Math-functions/to_border.c \
		src/Math-functions/is_whole.c \
		src/rendering/raycasting_image_handler.c \
		src/rendering/raycasting.c \
		src/utils.c
	
SRCSB =	bonus/main_bonus.c \
		bonus/parsing/parsing_file_bonus.c \
		bonus/parsing/parsing_map_bonus.c \
		bonus/parsing/textures_bonus.c \
		bonus/parsing/wall-checks_bonus.c \
		bonus/parsing/map-checks_bonus.c \
		bonus/parsing/parsing_utils_bonus.c \
		bonus/parsing/pfand_collect_bonus.c \
		bonus/rendering/init_window_bonus.c \
		bonus/rendering/init_canvas_bonus.c \
		bonus/rendering/mini_map_bonus.c \
		bonus/rendering/player_bonus.c \
		bonus/rendering/mini_raycasting_bonus.c \
		bonus/rendering/mouse_bonus.c \
		bonus/rendering/events_bonus.c \
		bonus/rendering/render_utils_bonus.c \
		bonus/rendering/raycasting_image_handler_bonus.c \
		bonus/rendering/raycasting_bonus.c \
		bonus/rendering/raycasting_utils_bonus.c \
		bonus/rendering/raycasting_objects_bonus.c \
		bonus/rendering/init_textures_bonus.c \
		bonus/rendering/shops_bonus.c \
		bonus/rendering/ui_bonus.c \
		bonus/Math-functions/distance_bonus.c \
		bonus/Math-functions/new_pos_bonus.c \
		bonus/Math-functions/radians_utils_bonus.c \
		bonus/Math-functions/to_border_bonus.c \
		bonus/Math-functions/is_whole_bonus.c \
		bonus/utils_bonus.c \
		bonus/init_env_bonus.c \
		bonus/Xmlx_bonus.c

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

all: $(MINILIBX_DIR) $(MINILIBX) $(LIBFT) $(NAME)

$(MINILIBX_DIR):
	git clone $(LIB_URL) $(MINILIBX_DIR)
	@echo "Downloading MiniLibX..."
$(MINILIBX): $(MINILIBX_DIR)
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MINILIBX) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  $(LIBFT) $(MINILIBX) $(FLAGS_MINILIBX) -o $(NAME)

bonus: $(MINILIBX) $(SRCSB)
	$(CC) $(CFLAGS) $(SRCSB)  $(LIBFT) $(MINILIBX) $(FLAGS_MINILIBX) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re