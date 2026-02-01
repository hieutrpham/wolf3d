/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:35:33 by trupham           #+#    #+#             */
/*   Updated: 2026/01/31 17:30:38 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
#include <fcntl.h>
#include <string.h>
# include "libft.h"
#include "MLX42/MLX42.h"

#define BUFFER_SIZE 64
# define MAX_FD 1024
#define RADIUS 50
#define BG 0x222222FF
#define RED 0xFF0000FF
# define FAIL 1
# define SUCC 0
# define WIDTH 1920
# define HEIGHT 1080
#define PI 3.14159265358979323846f
#define RAD 0.017453292519943295f
#define GREEN 0x00FF00FF
#define WALL_HEIGHT 600.0f
#define FOV 60
#define MINIMAP_SIZE 180

typedef struct
{
	int32_t r;
	int32_t g;
	int32_t b;
	int32_t a;
} t_color;

typedef struct
{
	int dx;
	int dy;
	int y1;
	int y2;
	int intercept;
} t_line;

typedef struct
{
	int x;
	int y;
} vector_t;

typedef struct {
	vector_t pos;
	float angle;
	float dx;
	float dy;
} t_player;

typedef struct {
	mlx_t *mlx;
	mlx_image_t *image;
	t_player *player;
	int mapX;
	int mapY;
	int *map;
} t_game;

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
int		flood_fill(char **map, int x, int y, t_bounds b);

char 	*get_path(char *line);
void 	skip_space(char **str);
void 	print_file(t_file *file);

// draw functions
void	key_control(mlx_key_data_t keydata, void *param);
void draw_map(void *param);
void clear_bg(void *param);
void draw_rectangle(mlx_image_t *image, vector_t origin, int width, int height, uint color);
void draw_line2(mlx_image_t *image, vector_t v1, vector_t v2, uint color);
void draw_line(mlx_image_t *image, vector_t v1, vector_t v2, uint color);
void	put_pixel(mlx_image_t *img, uint16_t x, uint16_t y, uint32_t color);
void swap_int(int *i1, int *i2);

// game
void game_loop(t_game *game);
int game_init(t_game *game);

//vector
vector_t build_v2(uint x, uint y);
vector_t v2_add(vector_t v1, vector_t v2);
vector_t v2_sub(vector_t v2, vector_t v1);
unsigned int v2_sqlen(vector_t v);
#endif
