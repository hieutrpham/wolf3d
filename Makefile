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
CFLAGS = -Wall -Werror -Wextra -Iinclude -I./include/

SRC_DIR = ./src
OBJ_DIR = ./object

MAIN_FILES = main.c message.c ft_strcmp.c get_next_line_bonus.c get_next_line_utils_bonus.c
# parsing.c

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES))
		
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(NAME)
#all:$(LIBFT_LIB) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS)

#cleaning
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
