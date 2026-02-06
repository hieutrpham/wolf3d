/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:27:40 by trupham           #+#    #+#             */
/*   Updated: 2026/02/06 14:57:51 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// draw a line from vector v1 to v2
// static void draw_line(mlx_image_t *image, t_vector v1, t_vector v2, uint color)
// {
// 	t_line line = {};
// 	int i;
// 	int j;
//
// 	line.dy = v2.y - v1.y;
// 	line.dx = v2.x - v1.x;
// 	if (line.dx != 0)
// 	{
// 		line.intercept = v2.y - (line.dy*v2.x)/line.dx;
// 		if (v1.x > v2.x)
// 			swap_int(&v1.x, &v2.x);
// 		for (i = v1.x; i < v2.x; i++)
// 		{
// 			line.y1 = line.dy*i/line.dx + line.intercept;
// 			line.y2 = line.dy*(i+1)/line.dx + line.intercept;
// 			if (line.y1 > line.y2)
// 				swap_int(&line.y1, &line.y2);
// 			for (j = line.y1; j <= line.y2; j++)
// 				put_pixel(image, i, j, color);
// 		}
// 	}
// 	else
// 	{
// 		if (v1.y > v2.y)
// 			swap_int(&v1.y, &v2.y);
// 		for (int y = v1.y; y < v2.y; y++)
// 			put_pixel(image, v2.x, y, color);
// 	}
// }

// draw infinite line given 2 vectors
// void draw_line2(mlx_image_t *image, t_vector v1, t_vector v2, uint color)
// {
// 	int dy = v2.y - v1.y;
// 	int dx = v2.x - v1.x;
//
// 	if (dx == 0 && dy == 0)
// 		return;
// 	if (dx != 0)
// 	{
// 		int y_intercept = v2.y - dy*v2.x/dx;
// 		if (dy != 0)
// 		{
// 			int x_intercept = -y_intercept*dx/dy;
// 			if (v2.y > v1.y) // lower quadrant
// 			{
// 				if (v2.x > v1.x)
// 				{
// 					x_intercept = (image->height - y_intercept)*dx/dy;
// 					draw_line(image, v1, (t_vector){x_intercept, image->height}, color);
// 				}
// 				else
// 				draw_line(image, v1, (t_vector){0, y_intercept}, color);
// 			}
// 			else // upper quadrant
// 				draw_line(image, v1, (t_vector){x_intercept, 0}, color);
// 		}
// 		else if (dy == 0)
// 		{
// 			if (v2.x < v1.x)
// 				draw_line(image, v1, (t_vector){0, v1.y}, color);
// 			if (v2.x > v1.x)
// 				draw_line(image, v1, (t_vector){image->width, v1.y}, color);
// 		}
// 	}
// 	else if (dx == 0)
// 	{
// 		if (v2.y < v1.y)
// 			draw_line(image, v1, (t_vector){v1.x, 0}, color);
// 		if (v2.y > v1.y)
// 			draw_line(image, v1, (t_vector){v1.x, image->height}, color);
// 	}
// }

void draw_strip(t_game *game, t_vector origin, int wall_height, int tx)
{
	int y_start;
	int y;
	uint color;

	y_start = (int)origin.y;
	y = 0;
	while (y < wall_height)
	{
		color = get_pixel_from_texture(game->we, tx, (int)(y*game->we->height/wall_height));
		put_pixel(game->image, (int)origin.x, y + y_start, color);
		y++;
	}
}

void draw_rectangle(mlx_image_t *image, t_vector origin, int width, int height, uint color)
{
	for (int y = (int)origin.y; y < (int)origin.y + height; y++)
		for (int x = (int)origin.x; x < (int)origin.x + width; x++)
			put_pixel(image, x, y, color);
}

