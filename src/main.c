/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:28:46 by trupham           #+#    #+#             */
/*   Updated: 2025/12/13 12:12:10 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cube3D.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

t_str *str_append(t_str *str, char *line)
{
	int i;

	i = 0;
	if (str->count >= str->cap)
	{
		if (str->cap == 0)
			str->cap = 256;
		else
			str->cap *=2;
		str->str = realloc(str->str, str->cap * sizeof(*str->str));
	}
	while (line[i] != '\n')
		str->str[str->count++] = line[i++];
	return str;
}

#if 0
int main(int argc, char *argv[])
{
	t_file	file;

	if (argc != 2)
		return (err_message("Usage: ./cub3D <map.cub>\n", FAIL));
	if (check_exter(argv[1]) == FAIL)
		return (err_message("map is wrong\n", FAIL));
	ft_bzero(&file, sizeof(t_file));
	if (check_inter(&file, argv[1]) == FAIL)
	{
		free_file(&file);
		return (FAIL);
	}
	free_file(&file);
	return (SUCC);
}
#else
#define RADIUS 50
#define BG 0x222222FF
#define RED 0xFF0000FF
typedef struct
{
	int32_t r;
	int32_t g;
	int32_t b;
	int32_t a;
} t_color;

typedef struct
{
	int x;
	int y;
} vector_t;

vector_t build_v2(uint x, uint y)
{
	return (vector_t){x, y};
}

vector_t v2_add(vector_t v1, vector_t v2) {
	vector_t ret = {v1.x + v2.x, v1.y + v2.y};
	return ret;
}

vector_t v2_sub(vector_t v2, vector_t v1) {
	vector_t ret = {v1.x - v2.x, v1.y - v2.y};
	return ret;
}

unsigned int v2_sqlen(vector_t v) {
	return v.x * v.x + v.y * v.y;
}

static mlx_image_t *image;

int32_t ft_pixel(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

// y = mx + b
// m is the slope, b is the intersect with y axis (when x == 0)
// we have 2 vector (x1, y1) (x2, y2) that satify the line equation
// y1 - m*x1 = y2 - m*x2
// y1 - y2 = mx1 - mx2
// m = (y1 - y2)/(x1 - x2)
// once we get the slope, just plug in the vector to solve for b

vector_t player_pos = {WIDTH/2, HEIGHT/2};

void	put_pixel(mlx_image_t *img, uint16_t x, uint16_t y, int color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

// y2 - y1 = mx2
void draw_line(void *param)
{
	mlx_t *mlx = param;
	int32_t mouse_x, mouse_y;
	mlx_get_mouse_pos(mlx, &mouse_x, &mouse_y);

	vector_t mouse_pos = build_v2(mouse_x, mouse_y);
	int64_t dx = player_pos.x - mouse_pos.x;
	int64_t dy = player_pos.y - mouse_pos.y;
	if (dx == 0)
	{
		for (uint32_t y = 0; y < image->height; y++)
			put_pixel(image, player_pos.x, y, RED);
	}
	else
	{
		int64_t slope = dy/dx;
		for (int x = player_pos.x; x < mouse_pos.x; x++)
		{
			int64_t y = (int32_t)(slope * (x - player_pos.x) + player_pos.y);
			put_pixel(image, x, y, RED);
		}
	}
}

void draw_circle(void *param)
{
	(void)param;
	uint radius = RADIUS;
	vector_t center = build_v2(WIDTH/2, HEIGHT/2);
	for (uint32_t y = 0; y < image->height; y++)
	{
		for (uint32_t x = 0; x < image->width; x++)
		{
			vector_t p = build_v2(x, y);
			vector_t d = v2_sub(p, center);
			if (v2_sqlen(d) <= radius * radius)
				mlx_put_pixel(image, x, y, 0xFF0000FF);
		}
	}
}

void clear_bg(void *param)
{
	(void)param;
	for (uint32_t y = 0; y < image->height; y++)
	{
		for (uint32_t x = 0; x < image->width; x++)
			mlx_put_pixel(image, x, y, BG);
	}
}

void game_loop(mlx_t *mlx)
{
	// mlx_loop_hook(mlx, draw_circle, mlx);
	// mlx_loop_hook(mlx, clear_bg, mlx);
	mlx_loop_hook(mlx, draw_line, mlx);
}

void	close_win(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int main()
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
		return 1;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
		return 1;
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, close_win, mlx);
	game_loop(mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
#endif
