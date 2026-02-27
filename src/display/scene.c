/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:05:05 by trupham           #+#    #+#             */
/*   Updated: 2026/02/16 13:16:27 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	render_ceiling(void *param)
{
	t_game	*game;
	int		y;
	int		x;

	game = param;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game->image, x, y, set_brightness(game->ceil_color,
					(HEIGHT / 2 - y) / BRIGHTNESS));
			x++;
		}
		y++;
	}
}

void	render_floor(void *param)
{
	t_game	*game;
	uint	y;
	uint	x;

	game = param;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game->image, x, y, set_brightness(game->floor_color, (y
						- HEIGHT / 2) / BRIGHTNESS));
			x++;
		}
		y++;
	}
}

mlx_texture_t	*select_texture(t_game *game, t_texture_type t)
{
	if (t == SO)
		return (game->so);
	if (t == WE)
		return (game->we);
	if (t == EA)
		return (game->ea);
	if (t == NO)
		return (game->no);
	return (NULL);
}

t_texture	init_text(t_game *game, t_uvmap uv, t_texture_type t)
{
	t_texture	text;

	text.texture = select_texture(game, t);
	text.brightness = fminf(1.0f, uv.height / BRIGHTNESS);
	text.draw_start = (int)uv.origin.y;
	if (text.draw_start < 0)
		text.offset = -text.draw_start;
	else
		text.offset = 0;
	text.step = (float)text.texture->height / (float)uv.height;
	text.tex_y = text.offset * text.step;
	text.draw_end = (int)text.draw_start + uv.height;
	if (text.draw_end > HEIGHT)
		text.draw_end = HEIGHT;
	if (text.draw_start < 0)
		text.draw_start = 0;
	return (text);
}

void	draw_texture(t_game *game, t_uvmap uv, t_texture_type t)
{
	t_texture	text;

	text = init_text(game, uv, t);
	while (text.draw_start < text.draw_end)
	{
		text.color = get_pixel_from_texture(text.texture, uv.tx,
				(int)(text.tex_y));
		put_pixel(game->image, (int)uv.origin.x, (int)text.draw_start,
			set_brightness(text.color, text.brightness));
		text.tex_y += text.step;
		text.draw_start++;
	}
}
