# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 12:30:39 by vinguyen          #+#    #+#              #
#    Updated: 2025/12/07 15:38:38 by trupham          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude

SRC_DIR = ./src
OBJ_DIR = ./object

MLX42_DIR = ./MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
MLX42_LINK_FLAGS = $(MLX42_LIB) -ldl -lglfw -pthread -lm
MLX42_FLAGS = -I$(MLX42_DIR)/include/

MAIN_FILES = main.c message.c ft_strcmp.c get_next_line_bonus.c get_next_line_utils_bonus.c \
			start_to_display.c
# parsing.c

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES))
		
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(NAME)
#all:$(LIBFT_LIB) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

$(MLX42_LIB):
	@echo "Cloning and building MLX42..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build

$(NAME): $(OBJ) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42_LINK_FLAGS) -o $(NAME) $(LDLIBS)
	@echo "cube3D execution created"

#cleaning
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
