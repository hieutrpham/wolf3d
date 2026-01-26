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
#include <math.h>
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

void	put_pixel(mlx_image_t *img, uint16_t x, uint16_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

void swap_int(int *i1, int *i2)
{
	int temp;

	temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}

typedef struct
{
	int dx;
	int dy;
	int y1;
	int y2;
	int intercept;
} t_line;

// draw a line from vector v1 to v2
void draw_line(mlx_image_t *image, vector_t v1, vector_t v2, uint color)
{
	t_line line = {};
	int i;
	int j;
	
	line.dy = v2.y - v1.y;
	line.dx = v2.x - v1.x;
	if (line.dx != 0)
	{
		line.intercept = v2.y - (line.dy*v2.x)/line.dx;
		if (v1.x > v2.x)
			swap_int(&v1.x, &v2.x);
		for (i = v1.x; i < v2.x; i++)
		{
			line.y1 = line.dy*i/line.dx + line.intercept;
			line.y2 = line.dy*(i+1)/line.dx + line.intercept;
			if (line.y1 > line.y2)
				swap_int(&line.y1, &line.y2);
			for (j = line.y1; j <= line.y2; j++)
				put_pixel(image, i, j, color);
		}
	}
	else
	{
		if (v1.y > v2.y)
			swap_int(&v1.y, &v2.y);
		for (int y = v1.y; y < v2.y; y++)
			put_pixel(image, v2.x, y, color);
	}
}

// draw infinite line given 2 vectors
void draw_line2(mlx_image_t *image, vector_t v1, vector_t v2, uint color)
{
	int dy = v2.y - v1.y;
	int dx = v2.x - v1.x;

	if (dx == 0 && dy == 0)
		return;
	if (dx != 0)
	{
		int y_intercept = v2.y - dy*v2.x/dx;
		if (dy != 0)
		{
			int x_intercept = -y_intercept*dx/dy;
			if (v2.y > v1.y) // lower quadrant
			{
				if (v2.x > v1.x)
				{
					x_intercept = (image->height - y_intercept)*dx/dy;
					draw_line(image, v1, (vector_t){x_intercept, image->height}, color);
				}
				else
				draw_line(image, v1, (vector_t){0, y_intercept}, color);
			}
			else // upper quadrant
				draw_line(image, v1, (vector_t){x_intercept, 0}, color);
		}
		else if (dy == 0)
		{
			if (v2.x < v1.x)
				draw_line(image, v1, (vector_t){0, v1.y}, color);
			if (v2.x > v1.x)
				draw_line(image, v1, (vector_t){image->width, v1.y}, color);
		}
	}
	else if (dx == 0)
	{
		if (v2.y < v1.y)
			draw_line(image, v1, (vector_t){v1.x, 0}, color);
		if (v2.y > v1.y)
			draw_line(image, v1, (vector_t){v1.x, image->height}, color);
	}
}

#define PI 3.14159265358979323846f
#define DR (PI/180f)
#define GREEN 0x00FF00FF

int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,1,
	1,0,1,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

#define mapX 8
#define mapY 8
#define cell_size (WIDTH/mapX)

// void draw_rays(void *param)
// {
// 	t_player *p = param;
// }

void clear_bg(void *param)
{
	(void)param;
	for (uint32_t y = 0; y < image->height; y++)
	{
		for (uint32_t x = 0; x < image->width; x++)
			put_pixel(image, x, y, BG);
	}
}

t_player player = {.angle = PI/2};

void draw_rectangle(mlx_image_t *image, vector_t origin, int width, int height, uint color)
{
	for (int y = origin.y; y < origin.y + height; y++)
		for (int x = origin.x; x < origin.x + width; x++)
			put_pixel(image, x, y, color);
}

void draw_map(void *param)
{
	t_game *game = param;
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapY; x++)
		{
			if (map[y*mapX + x] == 1)
				draw_rectangle(game->image, (vector_t){x * cell_size, y * HEIGHT/mapY}, cell_size, HEIGHT/mapY, 0x0000ffff);
			draw_line(game->image, (vector_t){x*cell_size, 0}, (vector_t){x*cell_size, HEIGHT}, 0x202020ff);
			draw_line(game->image, (vector_t){0, y*HEIGHT/mapY}, (vector_t){WIDTH, y*HEIGHT/mapY}, 0x202020ff);
		}
	}
}

void game_loop(t_game *game)
{
	// mlx_loop_hook(mlx, draw_circle, mlx);
	// mlx_loop_hook(game->mlx, clear_bg, NULL);
	mlx_loop_hook(game->mlx, draw_map, game);
	// mlx_loop_hook(mlx, draw_rays, &player);
}

void	key_control(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	// if (keydata.key == MLX_KEY_A)
}

int main()
{
	t_game game = {0};
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game.mlx)
		return 1;
	game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.image)
		return 1;
	mlx_image_to_window(game.mlx, game.image, 0, 0);
	mlx_key_hook(game.mlx, key_control, &game);
	game_loop(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return 0;
}
#endif
