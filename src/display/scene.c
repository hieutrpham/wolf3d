/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:05:05 by trupham           #+#    #+#             */
/*   Updated: 2026/02/06 14:32:42 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void render_ceiling(void *param)
{
	t_game *game;
	int y;
	int x;

	game = param;
	y = 0;
	while (y < HEIGHT/2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game->image, x, y, set_brightness(game->ceil_color, (HEIGHT/2-y)/BRIGHTNESS));
			x++;
		}
		y++;
	}
}

void render_floor(void *param)
{
	t_game *game;
	uint y;
	uint x;

	game = param;
	y = HEIGHT/2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game->image, x, y, set_brightness(game->floor_color, (y - HEIGHT/2)/BRIGHTNESS));
			x++;
		}
		y++;
	}
}

void draw_texture(t_game *game, t_uvmap uv, t_texture t)
{
	float y_start;
	uint color;
	float brightness;
	mlx_texture_t *texture = NULL;

	if (t == SO)
		texture = game->so;
	if (t == WE)
		texture = game->we;
	if (t == EA)
		texture = game->ea;
	if (t == NO)
		texture = game->no;
	brightness = fminf(1.0f, uv.height/BRIGHTNESS);
	y_start = uv.origin.y;

	int offset;
	int draw_start = (int)y_start;
	if (y_start < 0)
		offset = -draw_start;
	else
		offset = 0;
	float step = (float)texture->height/(float)uv.height;
	float tex_y = offset * step;
	int draw_end = (int)y_start + uv.height;

	if (draw_end > HEIGHT)
		draw_end = HEIGHT;
	if (draw_start < 0)
		draw_start = 0;
	while (draw_start < draw_end)
	{
		color = get_pixel_from_texture(texture, uv.tx, (int)(tex_y));
		put_pixel(game->image, (int)uv.origin.x, (int)draw_start, set_brightness(color, brightness));
		tex_y += step;
		draw_start++;
	}
}
