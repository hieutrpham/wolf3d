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
			put_pixel(game->image, x, y, CEILING);
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
			put_pixel(game->image, x, y, FLOOR);
			x++;
		}
		y++;
	}
}
