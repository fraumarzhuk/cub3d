NAME = cub3d
CC = cc
UNAME_S := $(shell uname -s)
CFLAGS = -Wall -Wextra -Werror -g -lm #-fsanitize=address
MINILIBX_TGZ_NAME = MiniLibX.tgz
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://cdn.intra.42.fr/document/document/26192/minilibx-linux.tgz
	FLAGS_MINILIBX = -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm
	MINILIBX_DIR = ./minilibx-linux
else ifeq ($(UNAME_S), Darwin)
	LIB_URL = https://cdn.intra.42.fr/document/document/26193/minilibx_opengl.tgz
	FLAGS_MINILIBX = -Lmlx -framework OpenGL -framework AppKit
	MINILIBX_DIR = ./minilibx_opengl_20191021
endif
SRCST =	src/Tobi/main.c \
		src/Math-functions/to_border_bonus.c \
		src/Math-functions/radians_utils_bonus.c \
		src/Math-functions/is_whole_bonus.c \
		src/Math-functions/distance_bonus.c \
		src/Math-functions/new_pos_bonus.c
		
SRCS =	src/main_bonus.c \
		src/parsing/parsing_file_bonus.c \
		src/parsing/parsing_map_bonus.c \
		src/parsing/textures_bonus.c \
		src/parsing/wall-checks_bonus.c \
		src/parsing/map-checks_bonus.c \
		src/parsing/parsing_utils_bonus.c \
		src/parsing/pfand_collect_bonus.c \
		src/rendering/init_window_bonus.c \
		src/rendering/init_canvas_bonus.c \
		src/rendering/mini_map_bonus.c \
		src/rendering/player_bonus.c \
		src/rendering/mini_raycasting_bonus.c \
		src/rendering/mouse_bonus.c \
		src/rendering/events_bonus.c \
		src/rendering/render_utils_bonus.c \
		src/rendering/raycasting_image_handler_bonus.c \
		src/rendering/raycasting_bonus.c \
		src/rendering/raycasting_utils_bonus.c \
		src/rendering/raycasting_objects_bonus.c \
		src/rendering/init_textures_bonus.c \
		src/rendering/shops_bonus.c \
		src/rendering/ui_bonus.c \
		src/Math-functions/distance_bonus.c \
		src/Math-functions/new_pos_bonus.c \
		src/Math-functions/radians_utils_bonus.c \
		src/Math-functions/to_border_bonus.c \
		src/Math-functions/is_whole_bonus.c \
		src/utils_bonus.c \
		src/init_env_bonus.c \
		src/Xmlx_bonus.c

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

all: $(MINILIBX_DIR) $(MINILIBX) $(LIBFT) $(NAME)

$(MINILIBX_DIR):
	@echo "Downloading MiniLibX for $(UNAME_S) from $(LIB_URL)"
	curl -L -o $(MINILIBX_TGZ_NAME) $(LIB_URL)
	@echo "Download completed."
	tar -xzf $(MINILIBX_TGZ_NAME)
	rm -f $(MINILIBX_TGZ_NAME)
$(MINILIBX): $(MINILIBX_DIR)
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MINILIBX) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  $(LIBFT) $(MINILIBX) $(FLAGS_MINILIBX) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re