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
CC = cc -g
CFLAGS = -Wall -Werror -Wextra -Wfloat-conversion -MMD -MP -Wunreachable-code -Ofast
SRC_DIR = ./src
SRC_SUBDIRS = 0_file_parsing 1_map_parsing utilities display control math game

OBJ_DIR = ./object

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MAIN_FILES = main.c \

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
      $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))

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
