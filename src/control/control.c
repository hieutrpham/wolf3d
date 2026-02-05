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

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_LEFT)
	{
		game->player->angle -= 0.1f;
		if (game->player->angle < 0)
			game->player->angle += 2*PI;
		game->player->dx = cosf(game->player->angle);
		game->player->dy = sinf(game->player->angle);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		game->player->angle += 0.1f;
		if (game->player->angle < 0)
			game->player->angle += 2*PI;
		game->player->dx = cosf(game->player->angle);
		game->player->dy = sinf(game->player->angle);
	}
	// BUG: fix A, D movements
	if (keydata.key == MLX_KEY_A)
		game->player->pos.x = game->player->pos.x - (int)game->player->dx * 0.5f;
	if (keydata.key == MLX_KEY_D)
		game->player->pos.x = game->player->pos.x + (int)game->player->dx * 0.5f;
	if (keydata.key == MLX_KEY_W)
	{
		game->player->pos.x = game->player->pos.x + (int)game->player->dx * 0.5f;
		game->player->pos.y = game->player->pos.y + (int)game->player->dy * 0.5f;
	}
	if (keydata.key == MLX_KEY_S)
	{
		game->player->pos.x = game->player->pos.x - (int)game->player->dx * 0.5f;
		game->player->pos.y = game->player->pos.y - (int)game->player->dy * 0.5f;
	}
}

