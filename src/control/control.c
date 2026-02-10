/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:37 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:33:55 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	key_control(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;
	t_player *p = game->player;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_LEFT)
	{
		p->angle -= 0.1f;
		if (p->angle < 0)
			p->angle += 2*PI;
		p->dir.x = cosf(p->angle);
		p->dir.y = sinf(p->angle);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		p->angle += 0.1f;
		if (p->angle > 2* PI)
			p->angle -= 2*PI;
		p->dir.x = cosf(p->angle);
		p->dir.y = sinf(p->angle);
	}
	if (keydata.key == MLX_KEY_A)
	{
		t_vector new_dir = {p->dir.y, -p->dir.x};
		p->pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED));
	}
	if (keydata.key == MLX_KEY_D)
	{
		t_vector new_dir = {-p->dir.y, p->dir.x};
		p->pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED));
	}
	if (keydata.key == MLX_KEY_W)
		p->pos = v2f_add(p->pos, v2f_scale(p->dir, SPEED));
	if (keydata.key == MLX_KEY_S)
		p->pos = v2f_sub(p->pos, v2f_scale(p->dir, SPEED));
}

