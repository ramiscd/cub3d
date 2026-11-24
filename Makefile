# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEPFLAGS	= -MMD -MP

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_MAIN	= main.c

SRC_PARSING	= parsing/parse_scene.c \
			  parsing/check_args.c \
			  parsing/read_file.c \
			  parsing/parse_elements.c \
			  parsing/parse_texture.c \
			  parsing/parse_color.c \
			  parsing/parse_map.c \
			  parsing/validate_map.c \
			  parsing/parse_utils.c \
			  parsing/free_scene.c

SRC_EXEC	= execution/init_game.c \
			  execution/init_textures.c \
			  execution/init_player.c \
			  execution/hooks.c \
			  execution/game_loop.c \
			  execution/movement.c \
			  execution/rotation.c \
			  execution/render.c \
			  execution/raycast.c \
			  execution/dda.c \
			  execution/draw_column.c \
			  execution/draw_utils.c \
			  execution/cleanup.c

SRC_UTILS	= utils/error.c \
			  utils/free_utils.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_MAIN) $(SRC_PARSING) \
				$(SRC_EXEC) $(SRC_UTILS))
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		= $(OBJS:.o=.d)

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

bonus:
	@echo "Bonus not implemented yet."

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

-include $(DEPS)
