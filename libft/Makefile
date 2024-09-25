NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS =  ft_calloc.c \
        ft_isprint.c \
        ft_memcpy.c \
        ft_putendl_fd.c \
        ft_strchr.c \
        ft_strlcat.c \
        ft_strncmp.c \
        ft_substr.c \
        ft_isalpha.c \
        ft_itoa.c \
        ft_memmove.c \
        ft_putnbr_fd.c \
        ft_strdup.c \
        ft_strlcpy.c \
        ft_strnstr.c \
        ft_tolower.c \
        ft_atoi.c \
        ft_isascii.c \
        ft_memchr.c \
        ft_memset.c \
        ft_putstr_fd.c \
        ft_striteri.c \
        ft_strlen.c \
        ft_strrchr.c \
        ft_toupper.c \
        ft_bzero.c \
        ft_isdigit.c \
        ft_memcmp.c \
        ft_putchar_fd.c \
        ft_split.c \
        ft_strjoin.c \
        ft_strmapi.c \
        ft_strtrim.c \
        ft_isalnum.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		utils.c \

SRCS += \
		leak_killer/ft_destructors.c \
		leak_killer/ft_allocs.c \
		leak_killer/ft_init.c \
		leak_killer/ft_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h leak_killer.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re