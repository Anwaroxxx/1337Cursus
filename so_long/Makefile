NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx -I./libft -I./includes -I./gnl -I./ft_printf

MLX_DIR = ./minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

GNL_DIR = ./gnl
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SRCS = src/main.c \
       src/map_parsing.c \
       src/map_validation.c \
       src/map_utils.c \
       src/render.c \
       src/events.c \
       src/game_logic.c \
       src/free.c \
       src/error.c \
       src/path_finding.c

ALL_SRCS = $(SRCS) $(GNL_SRCS)
OBJS = $(ALL_SRCS:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF_LIB):
	@make -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(LIBFT_LIB) $(FT_PRINTF_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(FT_PRINTF_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re