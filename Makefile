# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 12:30:39 by vinguyen          #+#    #+#              #
#    Updated: 2026/01/27 13:49:53 by trupham          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -Wfloat-conversion -Wunreachable-code -O3
SRC_DIR = ./src

FILE_PARS = $(SRC_DIR)/0_file_parsing
MAP_PARS = $(SRC_DIR)/1_map_parsing
UTILITIES = $(SRC_DIR)/utilities
DISPLAY = $(SRC_DIR)/display
CONTROL = $(SRC_DIR)/control
MATH = $(SRC_DIR)/math
GAME = $(SRC_DIR)/game

OBJ_DIR = ./object

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MAIN_FILES = main.c
PARS_FILES = 0_exter_inter.c  1_check_dir_fc.c  2_par_dir.c	3_par_fc.c  7_file_utilities.c
MAP_FILES = 0_map_copy.c  1_map_parse.c  7_map_utilities.c	8_free_map.c  9_for_debug.c
UTI_FILES = free_mem.c  helper.c  message.c
DIS_FILES = scene.c
CON_FILES = control.c handle_movement.c
MATH_FILES = vector.c
GAME_FILES = game.c ray_horizontal.c  rays.c  ray_vertical.c  texture.c

SRC =	$(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
		$(addprefix $(FILE_PARS)/, $(PARS_FILES)) \
		$(addprefix $(MAP_PARS)/, $(MAP_FILES)) \
		$(addprefix $(UTILITIES)/, $(UTI_FILES)) \
		$(addprefix $(DISPLAY)/, $(DIS_FILES)) \
		$(addprefix $(CONTROL)/, $(CON_FILES)) \
		$(addprefix $(MATH)/, $(MATH_FILES)) \
		$(addprefix $(GAME)/, $(GAME_FILES)) \

# MLX lib
LIBMLX = ./MLX42
LIBX := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

INCLUDE = -I. -Iinclude/ -I$(LIBMLX)/include -I./libft/

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: libmlx $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

libmlx:
	@git submodule update --init --recursive
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBX)

#cleaning
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
