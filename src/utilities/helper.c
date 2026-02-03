/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:30:56 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:32:53 by trupham          ###   ########.fr       */
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

// int32_t ft_pixel(t_color color)
// {
// 	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
// }

void	put_pixel(mlx_image_t *img, uint16_t x, uint16_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}
