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
} t_file;

int		err_message(char *string, int code);
int 	clean_up(char *map, char *line, int fd, int code);
void 	free_file(t_file *file);

int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int		has_nl(const char *str);
bool 	ft_strncmp(char *s1, char *s2, size_t n);

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

char 	*get_path(char *line);
void 	skip_space(char **str);
void 	print_file(t_file *file);

#endif
