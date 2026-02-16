/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_to_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:43 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:40:10 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	clear_bg(void *param)
{
	t_game	*game;

	game = param;
	for (uint32_t y = 0; y < game->image->height; y++)
	{
		for (uint32_t x = 0; x < game->image->width; x++)
			put_pixel(game->image, x, y, BG);
	}
}
