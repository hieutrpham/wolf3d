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
# include <MLX42/MLX42.h>

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

typedef struct s_file
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *floor;
	char *ceil;
	t_str *map;
} t_file;

typedef struct s_stex
{
	mlx_texture_t *no;
	mlx_texture_t *so;
	mlx_texture_t *we;
	mlx_texture_t *ea;
} t_tex;

typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t	*img;
	t_tex	tex;
	uint32_t floor_color;
	uint32_t ceil_color;
} t_game;

int	err_message(char *string, int code);
int	ft_strcmp(char *s1, char *s2);
int check_file(char *str);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int					has_nl(const char *str);
bool ft_strncmp(char *s1, char *s2, size_t n);

void    start_to_display(t_game *game, t_file *files);
void load_textures(t_game *game, t_file *files);

#endif
