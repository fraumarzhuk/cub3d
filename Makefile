NAME = cub3D
CC = cc
UNAME_S := $(shell uname -s)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MINILIBX_TGZ_NAME = MiniLibX.tgz
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://cdn.intra.42.fr/document/document/26192/minilibx-linux.tgz
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
		src/parsing/map-checks.c \
		src/rendering/init_window.c \
		src/rendering/mini_map.c \
		src/rendering/events.c \
		src/utils.c

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
	$(CC) $(CFLAGS) $(SRCS) $(FLAGS_MINILIBX) $(LIBFT) $(MINILIBX) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re