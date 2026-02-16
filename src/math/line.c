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

void	draw_rectangle(mlx_image_t *image, t_vector origin, int width,
		int height, uint color)
{
	for (int y = (int)origin.y; y < (int)origin.y + height; y++)
		for (int x = (int)origin.x; x < (int)origin.x + width; x++)
			put_pixel(image, x, y, color);
}
