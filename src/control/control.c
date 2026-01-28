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
	if (keydata.key == MLX_KEY_A)
	{
		game->player->angle -= 0.1f;
		if (game->player->angle < 0)
			game->player->angle += 2*PI;
		game->player->dx = cosf(game->player->angle) * 10;
		game->player->dy = sinf(game->player->angle) * 10;
	}
	if (keydata.key == MLX_KEY_D)
	{
		game->player->angle += 0.1f;
		if (game->player->angle < 0)
			game->player->angle += 2*PI;
		game->player->dx = cosf(game->player->angle) * 10;
		game->player->dy = sinf(game->player->angle) * 10;
	}
	if (keydata.key == MLX_KEY_W)
	{
		game->player->pos.x = game->player->pos.x + (int)game->player->dx;
		game->player->pos.y = game->player->pos.y + (int)game->player->dy;
	}
	if (keydata.key == MLX_KEY_S)
	{
		game->player->pos.x = game->player->pos.x - (int)game->player->dx;
		game->player->pos.y = game->player->pos.y - (int)game->player->dy;
	}
}

