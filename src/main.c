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

#include "../include/cube3D.h"
#include "MLX42/MLX42.h"
#include "cube3D.h"
#define ft_strdup strdup
#define ft_realloc realloc
#define ft_calloc calloc

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
		str->str = ft_realloc(str->str, str->cap * sizeof(*str->str));
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
#define WIDTH 1920
#define HEIGHT 1080
#define RADIUS 20
#define BG 0x222222FF
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

// vector_t v2_distance_sq(vector_t v1, vector_t v2) {
// 	return (vector_t){v2.x }
// }

static mlx_image_t *image;

int32_t ft_pixel(t_color color)
{
    return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

void draw(void *param)
{
	(void)param;
	uint radius = RADIUS;
	for (uint32_t y = 0; y < image->height; y++)
	{
		for (uint32_t x = 0; x < image->width; x++)
		{
			vector_t p = {x, y};
			if (v2_sqlen(p) <= radius * radius)
				mlx_put_pixel(image, x, y, 0xFF0000FF);
		}
	}
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
	mlx_loop_hook(mlx, draw, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
#endif
