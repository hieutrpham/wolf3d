/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:30:56 by trupham           #+#    #+#             */
/*   Updated: 2026/02/06 10:59:33 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void swap_int(int *i1, int *i2)
{
	int temp;

	temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}

uint set_brightness(uint color, float factor)
{
	float r;
	float g;
	float b;
	int a;

	if (factor < 0)
		factor = 0;
	if (factor > 1.0f)
		factor = 1.0f;
	r = ((color >> 24) & 0xFF) * factor;
	g = ((color >> 16) & 0xFF) * factor;
	b = ((color >> 8) & 0xFF) * factor;
	a = color & 0xFF;
	return (((int)r << 24 | (int)g << 16 | (int)b << 8) | a);
}

void	put_pixel(mlx_image_t *img, uint16_t x, uint16_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

uint get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

uint get_pixel_from_texture(mlx_texture_t *texture, int tx, int ty)
{
	int index;

	index = (ty * texture->width + tx) * texture->bytes_per_pixel;
	return (get_color(texture->pixels[index],
				   texture->pixels[index+1],
				   texture->pixels[index+2],
				   texture->pixels[index+3]));
}
