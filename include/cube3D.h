/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:35:33 by trupham           #+#    #+#             */
/*   Updated: 2026/02/19 15:12:16 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

# define SPEED 5.0f
# define BUFFER_SIZE 64
# define MAX_FD 1024
# define RADIUS 50
# define FAIL 1
# define SUCC 0
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846f
# define RAD 0.017453292519943295f
# define PROJECTION_DIST 1662
# define FOV 60
# define MINIMAP_SIZE 180
# define WHITE 0xffffffff
# define BRIGHTNESS 1000.0f
# define BG 0x222222FF
# define GRAY 0x303030ff
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define FLOOR 0x492828FF
# define CEILING 0x1A3263FF
# define CELL_SIZE 64
# define WALL '1'
# define SNAP_FACTOR 0.000001f
# define MOUSE_SENSITIVITY 0.001f
# define TURN_ANGLE 0.1f

typedef enum e_turn
{
	LEFT,
	RIGHT
}					t_turn;

typedef enum e_move
{
	FORWARD,
	BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT
}					t_move;

typedef enum e_texture_type
{
	EA,
	WE,
	NO,
	SO
}					t_texture_type;

typedef struct s_vector
{
	float			x;
	float			y;
}					t_vector;

/* struct containing info about the texture to be drawn
 origin is the top left coord of the texture
 height is the wall height that will be used to calculate the ratio
 between the texture height and wall height
 tx is the x coordinate of the texture to be sampled
*/
typedef struct s_uvmap
{
	t_vector		origin;
	int				height;
	int				tx;
	t_texture_type	texture;
}					t_uvmap;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	float			angle;
}					t_player;

typedef struct s_sect
{
	t_vector		hori;
	t_vector		vert;
}					t_sect;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		*player;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	uint			floor_color;
	uint			ceil_color;
	float			last_time;
	float			delta_time;
	float			delta_angle;
	int				map_width;
	int				map_height;
	char			**map;
	bool			forward;
	bool			backward;
	bool			left;
	bool			right;
	bool			turn_left;
	bool			turn_right;
	bool			mouse_enabled;
}					t_game;

typedef struct s_texture
{
	mlx_texture_t	*texture;
	float			brightness;
	float			step;
	float			tex_y;
	uint			color;
	int				offset;
	int				draw_start;
	int				draw_end;
}					t_texture;

typedef struct s_bounds
{
	int				w;
	int				h;
}					t_bounds;

typedef struct s_file
{
	int				fd;
	int				no_direc;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				fl_rgb[3];
	int				ce_rgb[3];
	int				fl;
	int				ce;
	int				start_map;
	int				err_dir;
	char			*map;
	int				line_count;
	char			**parse_map;
	int				map_height;
	int				map_width;
	int				player_x;
	int				player_y;
	char			player_dir;
}					t_file;

typedef struct s_ray
{
	float			dist;
	float			ray_angle;
	float			dist_hori;
	float			dist_vert;
	float			corrected_dist;
	float			line_offset;
	float			r_dir_y;
	float			r_dir_x;
	float			wall_height;
	t_uvmap			uv;
	t_sect			sect;
	int				r;
}					t_ray;

int					err_message(char *string, int code);
int					clean_up(char *map, char *line, int fd, int code);
void				free_file(t_file *file);
void				clean_game(t_game *game, t_file *file);

void				ft_bzero(void *s, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s);

int					check_exter(char *str);
int					check_inter(t_file *file, char *str);
int					check_dir_fc(t_file *file, char *line);
int					parse_dir_fc(t_file *file, char *line);
int					parse_no(t_file *file, char *line);
int					parse_so(t_file *file, char *line);
int					parse_we(t_file *file, char *line);
int					parse_ea(t_file *file, char *line);
int					parse_floor(t_file *file, char *line);
int					parse_ceil(t_file *file, char *line);
int					find_wall(char *line);
char				*check_dir(char *line, char *dir);

int					check_fc(t_file *file, char *line, char *dir);
int					check_color(char *num, int *color);
int					check_value(char *num, int *i);
int					process_infile(t_file *file);

int					map_read_from_file(t_file *file, char *line);
int					map_check(t_file *file);
int					map_wrong_character(t_file *file);
int					map_empty(t_file *file);
void				print_map(char **map);
void				find_height_width(t_file *file, char **map);
char				**pad_map(t_file *file, char **map);
void				clear_previous(char **str, int len);
void				free_2d_array(char **str);
void				find_player_pos(t_file *file);
int					player_can_move(t_file *file);
int					is_walkable(char c);
bool				in_bounds(t_file *file, int y, int x);
char				**arr_2d_copy(char **str, int len);
int					check_map_close(t_file *file);
int					flood_fill(char **map, int x, int y, t_bounds b);

char				*get_path(char *line);
void				skip_space(char **str);
void				print_file(t_file *file);

// control functions
void				key_control(mlx_key_data_t keydata, void *param);
void				turn(t_game *game, t_turn dir);
void				move(t_game *game, t_move dir);
void				move_left_or_right(t_game *game, t_move dir);
void				handle_movement(void *param);
// draw functions
void				draw_map(void *param);
void				clear_bg(void *param);
void				render_ceiling(void *param);
void				render_floor(void *param);
void				put_pixel(mlx_image_t *img, uint16_t x, uint16_t y,
						uint32_t color);
void				swap_int(int *i1, int *i2);
uint				set_brightness(uint color, float factor);
uint				get_color(int r, int g, int b, int a);
void				draw_texture(t_game *game, t_uvmap uv, t_texture_type t);
uint				get_pixel_from_texture(mlx_texture_t *texture, int tx,
						int ty);

// game
bool				load_texture(t_game *game, t_file *file);
void				game_loop(t_game *game);
bool				game_init(t_game *game, t_file *file, t_player *player);
t_sect				cast_ray(t_game *game, float player_angle);
bool				hit_wall(int map_x, int map_y, t_game *game);
void				get_vert_intersect(t_game *game, t_sect *sect,
						float player_angle);
void				get_hori_intersect(t_game *game, t_sect *sect,
						float player_angle);
void				draw_rays(void *param);
void				render_texture(t_ray ray, t_game *game);
void				unload_textures(t_game *game);

// vector
t_vector			v2f_build(float x, float y);
t_vector			v2f_add(t_vector v1, t_vector v2);
t_vector			v2f_sub(t_vector v2, t_vector v1);
t_vector			v2f_scale(t_vector v, float factor);
int					v2f_dot(t_vector v1, t_vector v2);
float				v2i_sqlen(t_vector v);
#endif
