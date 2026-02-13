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

#include "MLX42/MLX42.h"
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

void handle_movement(void *param)
{
	t_game *game = param;
	t_player *p = game->player;
	if (game->turn_left)
	{
		p->angle -= 0.1f;
		if (p->angle < 0)
			p->angle += 2*PI;
		p->dir.x = cosf(p->angle);
		p->dir.y = sinf(p->angle);
	}
	if (game->turn_right)
	{
		p->angle += 0.1f;
		if (p->angle > 2* PI)
			p->angle -= 2*PI;
		p->dir.x = cosf(p->angle);
		p->dir.y = sinf(p->angle);
	}
	if (game->left)
	{
		t_vector new_dir = {p->dir.y, -p->dir.x};
		t_vector new_pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED * (float)game->delta_time));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (game->right)
	{
		t_vector new_dir = {-p->dir.y, p->dir.x};
		t_vector new_pos = v2f_add(p->pos, v2f_scale(new_dir, SPEED * (float)game->delta_time));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (game->forward)
	{
		t_vector new_pos = v2f_add(p->pos, v2f_scale(p->dir, SPEED * (float)game->delta_time));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
	if (game->backward)
	{
		t_vector new_pos = v2f_sub(p->pos, v2f_scale(p->dir, SPEED * (float)game->delta_time));
		if (!is_wall(game, new_pos))
			p->pos = new_pos;
	}
}

void	key_control(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_LEFT)
			game->turn_left = true;
		if (keydata.key == MLX_KEY_RIGHT)
			game->turn_right = true;
		if (keydata.key == MLX_KEY_A)
			game->left = true;
		if (keydata.key == MLX_KEY_D)
			game->right = true;
		if (keydata.key == MLX_KEY_W)
			game->forward = true;
		if (keydata.key == MLX_KEY_S)
			game->backward = true;
	}
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_LEFT)
			game->turn_left = false;
		if (keydata.key == MLX_KEY_RIGHT)
			game->turn_right = false;
		if (keydata.key == MLX_KEY_A)
			game->left = false;
		if (keydata.key == MLX_KEY_D)
			game->right = false;
		if (keydata.key == MLX_KEY_W)
			game->forward = false;
		if (keydata.key == MLX_KEY_S)
			game->backward = false;
	}
}
