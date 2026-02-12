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
#define P_GIRTH 0.2f

bool is_wall(t_game *game, t_vector pos)
{
	int map_x = (int)pos.x;
	int map_y = (int)pos.y;
	if (map_x < 0)
		map_x = 0;
	if (map_y < 0)
		map_y = 0;
	return (game->map[map_y][map_x] == WALL);
}
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
		t_vector new_pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (keydata.key == MLX_KEY_D)
	{
		t_vector new_dir = {-p->dir.y, p->dir.x};
		t_vector new_pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (keydata.key == MLX_KEY_W)
	{
		t_vector new_pos = v2f_add(p->pos, v2f_scale(p->dir, SPEED));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (keydata.key == MLX_KEY_S)
	{
		t_vector new_pos = v2f_sub(p->pos, v2f_scale(p->dir, SPEED));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
}

