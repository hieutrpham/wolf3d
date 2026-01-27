/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:35:33 by trupham           #+#    #+#             */
/*   Updated: 2025/12/13 10:57:52 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
#include <fcntl.h>
#include <string.h>
// # include <MLX42/MLX42.h>

# include "libft.h"

# define FAIL 1
# define SUCC 0
# define WIDTH 800
# define HEIGHT 600

typedef struct s_str
{
	char *str;
	size_t count;
	size_t cap;
} t_str;

typedef struct s_bounds
{
	int	w;
	int	h;
}	t_bounds;

typedef struct s_file
{
	int		fd;
	int		no_direc;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		fl_rgb[3];
	int		ce_rgb[3];
	int		fl;
	int		ce;
	int		start_map;
	int		err_dir;
	char	*map;
	int		line_count;
	char	**parse_map;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_file;

int		err_message(char *string, int code);
int 	clean_up(char *map, char *line, int fd, int code);
void 	free_file(t_file *file);

void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);

int 	check_exter(char *str);
int 	check_inter(t_file *file, char *str);
int 	check_dir_fc(t_file *file, char *line);
int		parse_dir_fc(t_file *file, char *line);
int 	parse_no(t_file *file, char *line);
int 	parse_so(t_file *file, char *line);
int 	parse_we(t_file *file, char *line);
int 	parse_ea(t_file *file, char *line);
int 	parse_floor(t_file *file, char *line);
int 	parse_ceil(t_file *file, char *line);
int 	find_wall(char *line);
char 	*check_dir(char *line, char *dir);

int 	check_fc(t_file *file, char *line, char *dir);
int 	check_color(char *num, int *color);
int 	check_value(char *num, int *i);
int 	process_infile(t_file *file);

int 	map_read_from_file(t_file *file, char *line);
int 	map_check(t_file *file);
int		map_wrong_character(t_file *file);
int		map_empty(t_file *file);
void 	print_map(char **map);
void 	find_height_width(t_file *file, char **map);
char 	**pad_map(t_file *file, char **map);
void	clear_previous(char **str, int len);
void 	free_2d_array(char **str);
void	find_player_pos(t_file *file);
int 	player_can_move(t_file *file);
int		is_walkable(char c);
char 	**arr_2d_copy(char **str, int len);
int 	check_map_close(t_file *file);
// int		flood_fill(char **map, int x, int y, int w, int h);
int		flood_fill(char **map, int x, int y, t_bounds b);

char 	*get_path(char *line);
void 	skip_space(char **str);
void 	print_file(t_file *file);

#endif
