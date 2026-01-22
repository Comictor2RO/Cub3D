NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c collision.c draw_map.c draw_player.c hooks_handler.c utils.c map.c raycasting.c cleanup.c \
       parsing/parse_file.c parsing/parse_textures.c parsing/parse_colors.c \
       parsing/parse_map.c parsing/validate_map.c parsing/parse_utils.c parsing/parse_error.c
OBJS = $(SRCS:.c=.o)

MLX_PATH = ./minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

LIBFT_PATH = ./libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_PATH) -I$(LIBFT_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re