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
	int y_start;
	int y;
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
	brightness = uv.height/BRIGHTNESS;
	y_start = (int)uv.origin.y;
	y = 0;
	float step = (float)texture->height/(float)uv.height;
	while (y < uv.height)
	{
		color = get_pixel_from_texture(texture, uv.tx, (int)(y*step));
		put_pixel(game->image, (int)uv.origin.x, y + y_start, set_brightness(color, brightness));
		y++;
	}
}
